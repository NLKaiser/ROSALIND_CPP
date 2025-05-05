#include <iostream>
using namespace std;

/**
 * @brief Calculate the expected number of offspring with a dominant phenotype.
 * 
 * @param k Number of homozygous dominant individuals.
 * @param m Number of heterozygous individuals.
 * @param n Number of homozygous recessive individuals.
 * @return The expected number of offspring with a dominant phenotype.
 */
double expected_dominant_offspring(const int& k, const int& m, const int& n) {
    // Total number of individuals
    double total = k + m + n;
    double k_d = static_cast<double>(k);
    double m_d = static_cast<double>(m);
    double n_d = static_cast<double>(n);

    // Calculate the expected number of offspring with a dominant phenotype
    double expected = 0.0;
    expected += k_d/total * ((k_d - 1) / (total - 1) + m_d / (total - 1) + n_d / (total - 1)); // First is homozygous dominant
    expected += m_d/total * (k_d / (total - 1) + (m_d - 1) / (total - 1) * 0.75 + n_d / (total - 1) * 0.5); // First is heterozygous
    expected += n_d/total * (k_d / (total - 1) + m_d / (total - 1) * 0.5); // First is homozygous recessive

    return expected;
}

int main() {
    // Example input: k = 2, m = 2, n = 2
    int k = 2; int m = 2; int n = 2;
    double result = expected_dominant_offspring(k, m, n);
    cout << result << endl;
    return 0;
}