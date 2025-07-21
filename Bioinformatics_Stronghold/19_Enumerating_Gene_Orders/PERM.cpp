#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/**
 * @brief Calculate the number of distinct permutations.
 * 
 * @param n The total number of items.
 * @return A string containing the number of permutations followed by each permutation on a new line.
 */
string calculate_permutations(int n) {
    if (n <= 0) return "0"; // Base case

    long long num_permutations = 1;
    std::vector<int> permutation;
    for (int i = 1; i <= n; ++i) {
        num_permutations *= i; // Calculate factorial
        permutation.push_back(i); // Store the permutation
    }
    
    std::vector<std::vector<int>> all_perms;
    do {
        all_perms.push_back(permutation);
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    
    // Prepare the result string
    string result = to_string(num_permutations) + "\n";
    for (const auto& perm : all_perms) {
        for (size_t i = 0; i < perm.size(); ++i) {
            result += to_string(perm[i]);
            if (i < perm.size() - 1) {
                result += " ";
            }
        }
        result += "\n";
    }
    
    // Remove the trailing newline if it exists
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}

int main() {
    // Example n = 3
    int n = 3;
    
    string result = calculate_permutations(n);
    cout << result << endl;
    return 0;
}