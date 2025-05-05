#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Calculate the Hamming distance between two strings of equal length.
 * 
 * @param seq1 The first DNA sequence.
 * @param seq2 The second DNA sequence.
 * @return The Hamming distance between the two sequences.
 */
int hamming_distance(const string& seq1, const string& seq2) {
    int distance = 0;
    for (size_t i = 0; i < seq1.length(); ++i) {
        if (seq1[i] != seq2[i]) {
            ++distance;
        }
    }
    return distance;
}

int main() {
    // Example DNA sequences
    string seq1 = "GAGCCTACTAACGGGAT";
    string seq2 = "CATCGTAATGACGGCCT";

    int distance = hamming_distance(seq1, seq2);
    cout << distance << endl;
    return 0;
}