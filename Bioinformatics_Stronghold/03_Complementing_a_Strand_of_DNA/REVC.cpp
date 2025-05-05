#include <iostream>
#include <string>
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

int main() {
    // Example DNA sequence
    string dna_sequence = "AAAACCCGGT";
    string complemented_sequence = complement_dna(dna_sequence);
    cout << complemented_sequence << endl;
    return 0;
}