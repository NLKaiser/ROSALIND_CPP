#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * @brief Reverse complement a DNA sequence.
 * 
 * @param seq The DNA sequence.
 * @return The reverse complement of the sequence.
 */
string reverse_complement(const string& seq) {
    unordered_map<char, char> complement = {
        {'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}
    };
    string rev_comp = seq;
    reverse(rev_comp.begin(), rev_comp.end());
    for (char& c : rev_comp) {
        c = complement[c];
    }
    return rev_comp;
}

/**
 * @brief Translate a DNA sequence to a protein sequence.
 * 
 * @param seq The DNA sequence.
 * @return The translated protein sequence.
 */
string translate_dna_to_protein(const string& seq) {
    // Mapping of codons to amino acids
    unordered_map<string, string> codon_table = {
        {"ATG","M"}, // Start codon
        {"TTT","F"}, {"TTC","F"}, {"TTA","L"}, {"TTG","L"},
        {"CTT","L"}, {"CTC","L"}, {"CTA","L"}, {"CTG","L"},
        {"ATT","I"}, {"ATC","I"}, {"ATA","I"}, {"GTT","V"}, 
        {"GTC","V"}, {"GTA","V"}, {"GTG","V"}, {"TCT","S"}, 
        {"TCC","S"}, {"TCA","S"}, {"TCG","S"}, {"CCT","P"}, 
        {"CCC","P"}, {"CCA","P"}, {"CCG","P"}, {"ACT","T"}, 
        {"ACC","T"}, {"ACA","T"}, {"ACG","T"}, {"GCT","A"}, 
        {"GCC","A"}, {"GCA","A"}, {"GCG","A"}, {"TAT","Y"}, 
        {"TAC","Y"}, {"CAT","H"}, {"CAC","H"}, {"CAA","Q"}, 
        {"CAG","Q"}, {"AAT","N"}, {"AAC","N"}, {"AAA","K"}, 
        {"AAG","K"}, {"GAT","D"}, {"GAC","D"}, {"GAA","E"}, 
        {"GAG","E"}, {"GGT","G"}, {"GGC","G"}, {"GGA","G"}, 
        {"GGG","G"}, {"TGT","C"}, {"TGG","W"}, {"AGT","S"}, 
        {"AGC","S"}, {"CGT","R"}, {"CGC","R"}, {"CGA","R"}, 
        {"CGG","R"}, {"AGA","R"}, {"AGG","R"}, {"TGC","C"},
        {"TAA","Stop"}, {"TAG","Stop"}, {"TGA","Stop"} // Stop codons
    };
    
    string protein = "";
    for (size_t i = 0; i < seq.length(); i += 3) {
        string codon = seq.substr(i, 3);
        if (codon.length() < 3) {
            break; // Handle case where the last codon is incomplete
        }
        string amino_acid = codon_table[codon];
        if (amino_acid == "Stop") {
            break; // Stop translation when a stop codon is encountered
        }
        protein += amino_acid;
    }
    return protein;
}

/**
 * @brief Find open reading frames in a given reading frame.
 * 
 * @param seq The DNA sequence.
 * @return A vector of ORFs found in the sequence.
 */
vector<string> find_orf_in_reading_frame(const string& seq) {
    // Find all ORFs in the given reading frame
    vector<string> orfs;
    for (size_t i = 0; i < seq.length(); i += 3) {
        string codon = seq.substr(i, 3);
        if (codon == "ATG") {
            string orf = codon;
            for (size_t j = i + 3; j < seq.length(); j += 3) {
                string next_codon = seq.substr(j, 3);
                if (next_codon == "TAA" || next_codon == "TAG" || next_codon == "TGA") {
                    orfs.push_back(orf); // Store the ORF found
                    break;
                }
                orf += next_codon;
            }
        }
    }
    return orfs;
}

/**
 * @brief Find open reading frames in sequences from a FASTA file.
 * 
 * @param filename The name of the FASTA file.
 * @return A string representing the found ORFs.
 */
string find_orfs(const string& filename) {
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

    // Find ORFs in the sequences
    vector<string> orfs;
    for (const auto& seq : sequences) {
        // Find ORFs in the forward reading frames
        for (int rf = 0; rf < 3; ++rf) {
            string reading_frame = seq.substr(rf);
            vector<string> rf_orfs = find_orf_in_reading_frame(reading_frame);
            for (const auto& orf : rf_orfs) {
                string protein = translate_dna_to_protein(orf);
                if (!protein.empty()) {
                    orfs.push_back(protein); // Store the translated protein
                }
            }
        }

        // Reverse complement the sequence and find ORFs in all reading frames
        string rev_comp = reverse_complement(seq);
        for (int rf = 0; rf < 3; ++rf) {
            string reading_frame = rev_comp.substr(rf);
            vector<string> rf_orfs = find_orf_in_reading_frame(reading_frame);
            for (const auto& orf : rf_orfs) {
                string protein = translate_dna_to_protein(orf);
                if (!protein.empty()) {
                    orfs.push_back(protein); // Store the translated protein
                }
            }
        }
    }
    
    // Remove duplicates from the ORFs
    sort(orfs.begin(), orfs.end());
    orfs.erase(unique(orfs.begin(), orfs.end()), orfs.end());

    // Format the result
    string output = "";
    bool first = true;
    for (const auto& orf : orfs) {
        if (!first) output += "\n";
        first = false;
        output += orf;
    }
    return output;
}

int main() {
    // Example file
    string filename = "sequences.fasta";
    
    string orfs = find_orfs(filename);
    cout << orfs << endl;
    return 0;
}