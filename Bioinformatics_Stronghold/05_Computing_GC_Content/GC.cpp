#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * @brief Reads a FASTA file and returns the ID with the highest GC-content, followed by the GC-content of that string.
 * 
 * @param filename The name of the FASTA file to read.
 * @return A single string: ID and GC-content separated by a newline.
 */
string get_gc_from_fasta(const string& filename) {
    ifstream infile(filename);
    
    if (!infile) {
        cerr << "Error: Cannot open file " << filename << endl;
        return ""; // No GC content if file cannot be opened
    }
    
    float max_gc = 0;
    string max_id = "";

    string line;
    string current_id = "";
    string current_sequence = "";
    
    while (getline(infile, line)) {
        if (line.empty()) continue; // Skip empty lines
        if (line[0] == '>') {
            if (!current_id.empty()) {
                // Calculate GC content for the previous sequence
                int gc_count = 0;
                for (char nucleotide : current_sequence) {
                    if (nucleotide == 'G' || nucleotide == 'C') {
                        gc_count++;
                    }
                }
                float gc_content = static_cast<float>(gc_count) / current_sequence.length() * 100.0;
                
                // Update max GC content and ID if necessary
                if (gc_content > max_gc) {
                    max_gc = gc_content;
                    max_id = current_id;
                }
            }
            // New ID
            current_id = line.substr(1); // Remove '>'
            current_sequence = ""; // Initialize empty sequence
        } else {
            // Append sequence data
            current_sequence += line;
        }
    }
    
    // Handle the last sequence
    if (!current_id.empty()) {
        int gc_count = 0;
        for (char nucleotide : current_sequence) {
            if (nucleotide == 'G' || nucleotide == 'C') {
                gc_count++;
            }
        }
        float gc_content = static_cast<float>(gc_count) / current_sequence.length() * 100.0;

        if (gc_content > max_gc) {
            max_gc = gc_content;
            max_id = current_id;
        }
    }
    
    infile.close();
    return max_id + "\n" + to_string(max_gc);
}

int main() {
    // Example file
    string filename = "sequences.fasta";
    
    string max_gc = get_gc_from_fasta(filename);
    cout << max_gc << endl;
    return 0;
}