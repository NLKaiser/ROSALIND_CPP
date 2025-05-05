#include <iostream>
using namespace std;

/**
 * @brief Calculate the expected number of offspring with dominant phenotype
 *        from a given set of genotypes.
 * 
 * @param genotypes An array of integers representing the number of each genotype.
 * @return The expected number of offspring with dominant phenotype.
 */
double offspring_dominant_phenotype(const int (&genotypes)[6]) {
    // Genotypes:
    // genotypes[0] = AA-AA
    // genotypes[1] = AA-Aa
    // genotypes[2] = AA-aa
    // genotypes[3] = Aa-Aa
    // genotypes[4] = Aa-aa
    // genotypes[5] = aa-aa

    // Calculate the expected number of offspring with dominant phenotype
    double expected_offspring = 2 * (genotypes[0] + genotypes[1] + genotypes[2] + 0.75 * genotypes[3] + 0.5 * genotypes[4]);
    return expected_offspring;
}

int main() {
    // Example genotypes: 1 AA-AA, 0 AA-Aa, 0 AA-aa, 1 Aa-Aa, 0 Aa-aa, 1 aa-aa
    int genotypes[6] = {1, 0, 0, 1, 0, 1};
    
    double expected_offspring = offspring_dominant_phenotype(genotypes);
    cout << expected_offspring << endl;
    return 0;
}