#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Calculate the number of rabbit pairs after n months.
 * 
 * The Fibonacci sequence is used to model the growth of a rabbit population.
 * Each pair of rabbits produces a new pair every month, starting from the second month.
 * 
 * @param n The number of months.
 * @param m The lifespan of the rabbits in months.
 * @return The number of rabbit pairs after n months.
 */
long long mortal_fibonacci_rabbits(int n, int m) {
    vector<long long> ages(m, 0); // ages[0] = newborns
    ages[0] = 1; // start with 1 newborn pair

    for (int month = 1; month < n; ++month) {
        // Rabbits that are ready to reproduce (all rabbits except the newborns)
        long long newborns = 0;
        for (int i = 1; i < m; ++i) {
            newborns += ages[i];
        }

        // Age everyone: move rabbits one month older
        for (int i = m-1; i >= 1; --i) {
            ages[i] = ages[i-1];
        }
        ages[0] = newborns; // set the newborns
    }

    // Sum all living rabbits
    long long total = 0;
    for (int i = 0; i < m; ++i) {
        total += ages[i];
    }

    return total;
}

int main() {
    // Example n = 6, m = 3
    int n = 6; int m = 3;

    long long rabbits = mortal_fibonacci_rabbits(n, m);
    cout << rabbits << endl;
    return 0;
}