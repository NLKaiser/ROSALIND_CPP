#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Find N-glycosylation motifs in a FASTA file.
 * 
 * The N-glycosylation motif is defined as N{P}[ST]{P}.
 * 
 * @param filename The name of the FASTA file.
 * @return A string representing the IDs and positions of the motifs.
 */
string find_N_glycosylation_motif(const string& filename) {
    // Open the file
    ifstream infile(filename);
    
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    string line;
    vector<pair<string, vector<int>>> matches; // Store pairs of (ID, positions of motifs)
    string current_id = "";
    string current_sequence = "";
    
    while (getline(infile, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!current_sequence.empty()) {
                vector<int> positions;
                // Find N-glycosylation motifs in the current sequence
                for (size_t i = 0; i + 3 < current_sequence.size(); ++i) {
                    if (current_sequence[i] == 'N' && current_sequence[i + 1] != 'P' && (current_sequence[i + 2] == 'S' || current_sequence[i + 2] == 'T') && current_sequence[i + 3] != 'P') {
                        positions.push_back(i + 1); // Store 1-based index
                    }
                }
                if (!positions.empty()) {
                    matches.push_back({current_id, positions});
                }
                current_sequence.clear();
            }
            current_id = line.substr(1); // Remove '>'
        } else {
            current_sequence += line;
        }
    }
    // Add the last sequence
    if (!current_sequence.empty()) {
        vector<int> positions;
        // Find N-glycosylation motifs in the last sequence
        for (size_t i = 0; i + 3 < current_sequence.size(); ++i) {
            if (current_sequence[i] == 'N' && current_sequence[i + 1] != 'P' && (current_sequence[i + 2] == 'S' || current_sequence[i + 2] == 'T') && current_sequence[i + 3] != 'P') {
                positions.push_back(i + 1); // Store 1-based index
            }
        }
        if (!positions.empty()) {
            matches.push_back({current_id, positions});
        }
    }
    infile.close();

    // Format the result
    string output = "";
    bool first = true;
    for (const auto& match : matches) {
        if (!first) output += "\n";
        first = false;
        output += match.first + "\n";
        for (size_t i = 0; i < match.second.size(); ++i) {
            output += to_string(match.second[i]);
            if (i < match.second.size() - 1) output += " ";
        }
    }
    return output;
}

int main() {
    // Example file
    string filename = "proteins.fasta";

    string matches = find_N_glycosylation_motif(filename);
    cout << matches << endl;
    return 0;
}