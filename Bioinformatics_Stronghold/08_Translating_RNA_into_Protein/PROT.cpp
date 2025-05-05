#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

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

int main() {
    // Example RNA sequence
    string rna_sequence = "AUGGCCAUGGCGCCCAGAACUGAGAUCAAUAGUACCCGUAUUAACGGGUGA";
    
    string protein_sequence = translate_rna_to_protein(rna_sequence);
    cout << protein_sequence << endl;
    return 0;
}