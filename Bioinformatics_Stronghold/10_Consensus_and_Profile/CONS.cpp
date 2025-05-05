#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Get the consensus string and profile matrix from a FASTA file.
 * 
 * @param filename The name of the FASTA file.
 * @return A string containing the consensus string and profile matrix.
 */
string consensus_and_profile(const string& filename) {
    // Open the file
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }
    
    string line;
    string current_sequence = "";
    bool initialized = false;
    int length = 0;
    vector<vector<int>> profile(4); // Rows: A, C, G, T

    while (getline(infile, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!current_sequence.empty()) {
                // Initialise the profile with the length of the first sequence
                if (!initialized) {
                    length = current_sequence.size();
                    profile = vector<vector<int>>(4, vector<int>(length, 0));
                    initialized = true;
                }
                // Process sequence into profile
                for (int i = 0; i < current_sequence.size(); ++i) {
                    char c = current_sequence[i];
                    switch (c) {
                        case 'A': profile[0][i]++; break;
                        case 'C': profile[1][i]++; break;
                        case 'G': profile[2][i]++; break;
                        case 'T': profile[3][i]++; break;
                    }
                }
                current_sequence.clear();
            }
        } else {
            current_sequence += line;
        }
    }

    // Process the last sequence
    if (!current_sequence.empty()) {
        for (int i = 0; i < current_sequence.size(); ++i) {
            char c = current_sequence[i];
            switch (c) {
                case 'A': profile[0][i]++; break;
                case 'C': profile[1][i]++; break;
                case 'G': profile[2][i]++; break;
                case 'T': profile[3][i]++; break;
            }
        }
    }

    infile.close();

    // Generate consensus string
    string consensus = "";
    for (int i = 0; i < length; ++i) {
        int max_count = 0;
        char max_char = 'A';
        for (int j = 0; j < 4; ++j) {
            if (profile[j][i] > max_count) {
                max_count = profile[j][i];
                switch (j) {
                    case 0: max_char = 'A'; break;
                    case 1: max_char = 'C'; break;
                    case 2: max_char = 'G'; break;
                    case 3: max_char = 'T'; break;
                }
            }
        }
        consensus += max_char;
    }

    // Profile to string
    string profile_str = "";
    char labels[4] = {'A', 'C', 'G', 'T'};

    for (int row = 0; row < 4; ++row) {
        profile_str += labels[row];
        profile_str += ":";
        for (int col = 0; col < length; ++col) {
            profile_str += " " + to_string(profile[row][col]);
        }
        if (row < 3) { // Avoid adding a newline after the last row
            profile_str += "\n";
        }
    }

    return consensus + "\n" + profile_str;
}

int main() {
    // Example file
    string filename = "sequences.fasta";
    
    string result = consensus_and_profile(filename);
    cout << result << endl;
    return 0;
}