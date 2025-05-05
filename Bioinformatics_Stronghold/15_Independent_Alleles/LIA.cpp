#include <iostream>
#include <cmath>
using namespace std;

/**
 * @brief Calculate the binomial coefficient C(n, k).
 * 
 * @param n The total number of items.
 * @param k The number of items to choose.
 * @return The binomial coefficient C(n, k).
 */
double binomial_coefficient(int n, int k) {
    double res = 1.0;
    for (int i = 1; i <= k; ++i) {
        res *= (n - i + 1) / static_cast<double>(i);
    }
    return res;
}

/**
 * @brief Calculate the probability of having at least N individuals with a specific genotype.
 * 
 * @param k The generation number.
 * @param N The minimum number of individuals with the genotype.
 * @return The probability of having at least N individuals with the genotype.
 */
double independent_alleles(int k, int N) {
    int total_individuals = pow(2, k); // Total individuals in generation k
    double p = 0.25;   // Probability of Aa Bb

    double probability = 0.0;
    for (int i = N; i <= total_individuals; ++i) {
        double binom = binomial_coefficient(total_individuals, i);
        probability += binom * pow(p, i) * pow(1 - p, total_individuals - i);
    }
    return probability;
}

int main() {
    // Example k = 2, N = 1
    int k = 2; int N = 1;

    double probability = independent_alleles(k, N);
    cout << probability << endl;
    return 0;
}