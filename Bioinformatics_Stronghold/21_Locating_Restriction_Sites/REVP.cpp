#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief Complements a DNA sequence by replacing 'A' with 'T', 'T' with 'A',
 *        'C' with 'G', and 'G' with 'C'.
 * 
 * @param dna_sequence A string representing the DNA sequence.
 * @return A string representing the reverse complement.
 */
string complement_dna(const string& dna_sequence) {
    string complemented_sequence = dna_sequence;
    reverse(complemented_sequence.begin(), complemented_sequence.end()); // Reverse the sequence
    for (char& nucleotide : complemented_sequence) {
        switch (nucleotide) {
            case 'A':
                nucleotide = 'T'; // Replace 'A' with 'T'
                break;
            case 'T':
                nucleotide = 'A'; // Replace 'T' with 'A'
                break;
            case 'C':
                nucleotide = 'G'; // Replace 'C' with 'G'
                break;
            case 'G':
                nucleotide = 'C'; // Replace 'G' with 'C'
                break;
        }
    }
    return complemented_sequence;
}

/**
 * @brief Find palindromic restriction sites having length between 4 and 12 in a DNA sequence.
 * 
 * @param filename The name of the FASTA file containing the DNA sequence.
 * @return A string containing the position and length of every reverse palindrome.
 */
string find_palindromes(const string& filename) {
    ifstream infile(filename);
    
    if (!infile) {
        cerr << "Error: Cannot open file " << filename << endl;
        return ""; // No GC content if file cannot be opened
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

    string result;
    bool first_output_block = true;
    
    for (const auto& seq_pair : sequences) {
        const string& seq = seq_pair.second;
        string block;
        
        for (size_t i = 0; i < seq.length(); ++i) {
            for (size_t j = 4; j <= 12 && i + j <= seq.length(); ++j) {
                string substring = seq.substr(i, j);
                string reverse_substring = complement_dna(substring);
                if (substring == reverse_substring) {
                    block += to_string(i + 1) + " " + to_string(j) + "\n";
                }
            }
        }
        
        // New line between different sequences
        if (!block.empty()) {
            if (!first_output_block) {
                result += "\n";  // Only add newline if not first and block is non-empty
            }
            result += block;
            first_output_block = false;
        }
    }

    // Remove the trailing newline if it exists
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}

int main() {
    // Example file
    string filename = "sequences.fasta";
    
    string restriction_sites = find_palindromes(filename);
    cout << restriction_sites << endl;
    return 0;
}