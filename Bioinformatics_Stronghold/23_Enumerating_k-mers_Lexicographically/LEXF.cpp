#include <iostream>
#include <string>
#include <functional>
using namespace std;

/**
 * @brief Generates all k-mers of length n from a given alphabet in lexicographic order.
 * 
 * @param alphabet A string representing the sorted alphabet from which k-mers are generated.
 * @param n The length of the k-mers to be generated.
 * @return A string containing all k-mers in lexicographic order.
 */
string generate_kmers(const string& alphabet, int n) {
    string result;
    
    // Generate k-mers using a recursive approach
    function<void(string, int)> generate = [&](string current, int length) {
        if (length == n) {
            result += current + "\n";
            return;
        }
        for (char c : alphabet) {
            generate(current + c, length + 1);
        }
    };
    
    generate("", 0);
    // Remove the trailing newline if it exists
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}

int main() {
    // Example input
    string alphabet = "ACGT";
    int n = 2;

    string kmers = generate_kmers(alphabet, n);
    cout << kmers << endl;
    return 0;
}