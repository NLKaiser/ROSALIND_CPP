#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * @brief Transcribes a DNA sequence into an RNA sequence by replacing 'T' with 'U'.
 * 
 * @param dna_sequence A string representing the DNA sequence.
 * @return A string representing the transcribed RNA sequence.
 */
string transcribe_dna_to_rna(const string& dna_sequence) {
    string rna_sequence = dna_sequence;
    for (char& nucleotide : rna_sequence) {
        if (nucleotide == 'T') {
            nucleotide = 'U'; // Replace 'T' with 'U'
        }
    }
    return rna_sequence;
}

/**
 * @brief Translate an RNA sequence into a protein sequence.
 * 
 * @param rna_sequence The RNA sequence to be translated.
 * @return The corresponding protein sequence.
 */
string translate_rna_to_protein(const string& rna_sequence) {
    unordered_map<string, char> codon_table = {
        {"UUU", 'F'}, {"UUC", 'F'}, {"UUA", 'L'}, {"UUG", 'L'},
        {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'},
        {"UAU", 'Y'}, {"UAC", 'Y'}, {"UAA", '_'}, {"UAG", '_'},
        {"UGU", 'C'}, {"UGC", 'C'}, {"UGA", '_'}, {"UGG", 'W'},
        {"CUU", 'L'}, {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'},
        {"CCU", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
        {"CAU", 'H'}, {"CAC", 'H'}, {"CAA", 'Q'}, {"CAG", 'Q'},
        {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'},
        {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'}, {"AUG", 'M'},
        {"ACU", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
        {"AAU", 'N'}, {"AAC", 'N'}, {"AAA", 'K'}, {"AAG", 'K'},
        {"AGU", 'S'}, {"AGC", 'S'}, {"AGA", 'R'}, {"AGG", 'R'},
        {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'},
        {"GCU", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
        {"GAU", 'D'}, {"GAC", 'D'}, {"GAA", 'E'}, {"GAG", 'E'},
        {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'}
    };
    string protein_sequence = "";
    
    for (size_t i = 0; i < rna_sequence.length(); i += 3) {
        string codon = rna_sequence.substr(i, 3);
        
        if (codon.length() < 3) {
            break; // Handle case where the last codon is incomplete
        }
        char amino_acid = codon_table[codon];
        if (amino_acid == '_') {
            break; // Stop translation at stop codon
        }
        protein_sequence += amino_acid;
    }

    return protein_sequence;
}

/**
 * @brief Remove introns from a DNA sequence, transcribe it to mRNA and then translate it to a protein sequence.
 * 
 * @param filename The name of the FASTA file containing the DNA sequence and introns.
 * @return A string representing the protein sequence after splicing.
 */
string to_protein(const string& filename) {
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
    
    string dna_sequence = sequences[0].second; // The first sequence is the DNA sequence
    // Remove introns from the DNA sequence
    for (size_t i = 1; i < sequences.size(); ++i) {
        const string& intron = sequences[i].second;
        size_t pos = dna_sequence.find(intron);
        while (pos != string::npos) {
            dna_sequence.erase(pos, intron.length());
            pos = dna_sequence.find(intron, pos);
        }
    }

    // Transcribe the remaining DNA sequence to RNA
    string rna_sequence = transcribe_dna_to_rna(dna_sequence);
    // Translate the RNA sequence to a protein sequence
    string protein_sequence = translate_rna_to_protein(rna_sequence);

    return protein_sequence;
}

int main() {
    // Example file
    string filename = "sequences.fasta";
    
    string protein = to_protein(filename);
    cout << protein << endl;
    return 0;
}