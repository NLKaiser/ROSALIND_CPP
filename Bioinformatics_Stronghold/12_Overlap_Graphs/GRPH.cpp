#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Create an overlap graph from a FASTA file.
 * 
 * @param filename The name of the FASTA file.
 * @param k The length of the overlap.
 * @return A string representing the edges of the overlap graph.
 */
string overlap_graph(const string& filename, const int& k) {
    // Open the file
    ifstream infile(filename);
    
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    string line;
    vector<pair<string, string>> sequences; // Store pairs of (ID, sequence)
    string current_id = "";
    string current_sequence = "";
    
    while (getline(infile, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!current_sequence.empty()) {
                sequences.push_back({current_id, current_sequence});
                current_sequence.clear();
            }
            current_id = line.substr(1); // Remove '>'
        } else {
            current_sequence += line;
        }
    }

    // Add the last sequence
    if (!current_sequence.empty()) {
        sequences.push_back({current_id, current_sequence});
    }

    infile.close();

    // Create the overlap graph
    vector<string> result;
    for (const auto& seq1 : sequences) {
        for (const auto& seq2 : sequences) {
            if (seq1.first != seq2.first && seq1.second.substr(seq1.second.size() - k) == seq2.second.substr(0, k)) {
                result.push_back(seq1.first + " " + seq2.first);
            }
        }
    }
    
    // Format the result
    string output = "";
    bool first = true;
    for (const auto& edge : result) {
        if (!first) output += "\n";
        first = false;
        output += edge;
    }

    return output;
}

int main() {
    // Example file
    string filename = "sequences.fasta";
    int k = 3; // Length of the overlap

    string overlaps = overlap_graph(filename, k);
    cout << overlaps << endl;
    return 0;
}