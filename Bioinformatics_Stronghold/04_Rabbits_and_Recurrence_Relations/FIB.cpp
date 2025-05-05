#include <iostream>
using namespace std;

/**
 * @brief Calculates the number of rabbits after n months, given that each pair of rabbits produces k pairs of offspring every month.
 * 
 * @param n The number of months.
 * @param k The number of offspring produced by each pair of rabbits every month.
 * @return The total number of rabbits after n months.
 */
long long F_n(const int& n, const int& k) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    return F_n(n - 1, k) + k * F_n(n - 2, k);
}

int main() {
    // Example n = 5, k = 3
    int n = 5; int k = 3;
    long long rabbits = F_n(n, k);
    cout << rabbits << endl; // Output the number of rabbits after n months
    return 0;
}