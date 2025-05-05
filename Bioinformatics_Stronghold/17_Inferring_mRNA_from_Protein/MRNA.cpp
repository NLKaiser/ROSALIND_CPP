#include <iostream>
#include <string>
#include <map>
using namespace std;

/**
 * @brief Count the number of possible mRNA sequences that can encode a given protein.
 * 
 * @param protein The protein sequence represented as a string.
 * @return The number of possible mRNA sequences modulo 1,000,000.
 */
int count_mRNA_possibilities(const string& protein) {
    map<char, int> aa_to_mrna_count;

    // Define the amino acids and their codon counts
    aa_to_mrna_count['A'] = 4;  // Alanine (A) has 4 codons
    aa_to_mrna_count['C'] = 2;  // Cysteine (C) has 2 codons
    aa_to_mrna_count['D'] = 2;  // Aspartic acid (D) has 2 codons
    aa_to_mrna_count['E'] = 2;  // Glutamic acid (E) has 2 codons
    aa_to_mrna_count['F'] = 2;  // Phenylalanine (F) has 2 codons
    aa_to_mrna_count['G'] = 4;  // Glycine (G) has 4 codons
    aa_to_mrna_count['H'] = 2;  // Histidine (H) has 2 codons
    aa_to_mrna_count['I'] = 3;  // Isoleucine (I) has 3 codons
    aa_to_mrna_count['K'] = 2;  // Lysine (K) has 2 codons
    aa_to_mrna_count['L'] = 6;  // Leucine (L) has 6 codons
    aa_to_mrna_count['M'] = 1;  // Methionine (M) has 1 codon (start codon)
    aa_to_mrna_count['N'] = 2;  // Asparagine (N) has 2 codons
    aa_to_mrna_count['P'] = 4;  // Proline (P) has 4 codons
    aa_to_mrna_count['Q'] = 2;  // Glutamine (Q) has 2 codons
    aa_to_mrna_count['R'] = 6;  // Arginine (R) has 6 codons
    aa_to_mrna_count['S'] = 6;  // Serine (S) has 6 codons
    aa_to_mrna_count['T'] = 4;  // Threonine (T) has 4 codons
    aa_to_mrna_count['V'] = 4;  // Valine (V) has 4 codons
    aa_to_mrna_count['W'] = 1;  // Tryptophan (W) has 1 codon
    aa_to_mrna_count['Y'] = 2;  // Tyrosine (Y) has 2 codons
    aa_to_mrna_count['*'] = 3;  // Stop codon (*) has 3 possibilities

    int total = 1;
    for (char aa : protein) {
        total *= aa_to_mrna_count[aa];
        total %= 1000000; // Take modulo 1,000,000 at each step to prevent overflow
    }
    // The last amino acid is a stop codon, which has 3 possibilities
    total *= 3;
    // Take modulo 1,000,000
    total %= 1000000;
    return total;
}

int main() {
    // Example protein sequence: "MA"
    string protein = "MA";
    
    int count = count_mRNA_possibilities(protein);
    cout << count << endl;
    return 0;
}