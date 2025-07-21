#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * @brief Calculates the total monoisotopic mass of a protein string.
 * 
 * @param protein The protein sequence.
 * @return The total monoisotopic mass.
 */
double calculate_protein_mass(const string& protein) {
    // Monoisotopic mass table
    unordered_map<char, double> mass_table = {
        {'A', 71.03711}, {'C', 103.00919}, {'D', 115.02694}, {'E', 129.04259},
        {'F', 147.06841}, {'G', 57.02146}, {'H', 137.05891}, {'I', 113.08406},
        {'K', 128.09496}, {'L', 113.08406}, {'M', 131.04049}, {'N', 114.04293},
        {'P', 97.05276}, {'Q', 128.05858}, {'R', 156.10111}, {'S', 87.03203},
        {'T', 101.04768}, {'V', 99.06841}, {'W', 186.07931}, {'Y', 163.06333}
    };

    double total_mass = 0.0;
    for (char aa : protein) {
        total_mass += mass_table[aa];
    }
    return total_mass;
}

int main() {
    // Example protein sequence
    string protein = "SKADYEK";

    double mass = calculate_protein_mass(protein);
    cout << mass << endl;
    return 0;
}