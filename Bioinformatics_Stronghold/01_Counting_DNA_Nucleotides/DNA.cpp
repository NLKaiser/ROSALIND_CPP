#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Counts the number of A, C, G, and T nucleotides in a DNA sequence.
 * 
 * @param sequence A string representing the DNA sequence.
 * @return A string with counts of 'A', 'C', 'G', and 'T' separated by spaces.
 */
string count_dna(const string& sequence){
    int a = 0, c = 0, g = 0, t = 0;
    for (char nucleotide : sequence) {
        switch (nucleotide) {
            case 'A': a++; break;
            case 'C': c++; break;
            case 'G': g++; break;
            case 'T': t++; break;
        }
    }
    return to_string(a) + " " + to_string(c) + " " + to_string(g) + " " + to_string(t);
}

int main() {
    // Example DNA sequence
    string sequence = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC";
    string result = count_dna(sequence);
    cout << result << endl;
    return 0;
}