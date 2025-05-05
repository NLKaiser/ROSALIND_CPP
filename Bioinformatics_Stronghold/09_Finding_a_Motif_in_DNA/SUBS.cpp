#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Find all occurrences of a motif in a DNA sequence.
 * 
 * @param dna_sequence The DNA sequence to search in.
 * @param motif The motif to search for.
 * @return A string containing the positions of the motif in the DNA sequence.
 */
string find_motif_in_dna(const string& dna_sequence, const string& motif) {
    size_t pos = dna_sequence.find(motif);
    string positions = ""; // Initialize positions as an empty string
    bool first = true;
    
    while (pos != string::npos) {
        if (!first) {
            positions += " "; // Add space between positions
        }
        positions += to_string(pos + 1); // Store positions as 1-based index
        first = false;
        pos = dna_sequence.find(motif, pos + 1); // look again starting one after
    }
    
    return positions;
}

int main() {
    // Example DNA sequence and motif
    string dna_sequence = "GATATATGCATATACTT";
    string motif = "ATAT";
    
    string positions = find_motif_in_dna(dna_sequence, motif);
    cout << positions << endl;
    return 0;
}