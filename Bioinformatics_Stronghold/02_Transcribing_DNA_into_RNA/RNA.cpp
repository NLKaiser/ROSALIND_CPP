#include <iostream>
#include <string>
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

int main() {
    // Example DNA sequence
    string dna_sequence = "GATGGAACTTGACTACGTAAATT";
    string rna_sequence = transcribe_dna_to_rna(dna_sequence);
    cout << rna_sequence << endl; // Output: GAUGGAACUUGACUACGUAAAUU
    return 0;
}