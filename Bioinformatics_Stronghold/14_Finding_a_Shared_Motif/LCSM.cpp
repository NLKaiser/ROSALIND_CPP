#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Find the longest common substring in a FASTA file.
 * 
 * @param filename The name of the FASTA file.
 * @return The longest common substring.
 */
string shared_motif(const string& filename) {
    // Open the file
    ifstream infile(filename);
    
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    string line;
    vector<string> sequences;
    string current_sequence = "";
    
    while (getline(infile, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!current_sequence.empty()) {
                sequences.push_back(current_sequence);
                current_sequence.clear();
            }
        } else {
            current_sequence += line;
        }
    }

    // Add the last sequence
    if (!current_sequence.empty()) {
        sequences.push_back(current_sequence);
    }

    infile.close();

    // Find the longest common substring
    string shortest = sequences[0];
    for (const auto& seq : sequences) {
        if (seq.length() < shortest.length()) {
            shortest = seq;
        }
    }
    int min_len = shortest.length();

    string longest_common_substring = "";
    for (int len = min_len; len > 0; --len) {
        for (int start = 0; start <= min_len - len; ++start) {
            string substring = shortest.substr(start, len);
            bool found = true;
            for (const auto& seq : sequences) {
                if (seq.find(substring) == string::npos) {
                    found = false;
                    break;
                }
            }
            if (found) {
                longest_common_substring = substring;
                break;
            }
        }
        if (!longest_common_substring.empty()) {
            break;
        }
    }
    return longest_common_substring;
}

int main() {
    // Example file
    string filename = "sequences.fasta";

    string motif = shared_motif(filename);
    cout << motif << endl;
    return 0;
}