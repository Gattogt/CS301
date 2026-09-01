/*
 * Marcus Duggs
 * CS 12
 * Exercise #: [fill in exercise number]
 * Project: Permutations! (Johnson-Trotter Algorithm)
 *
 * Generates all permutations of the set {1, 2, ..., n} using the
 * Johnson-Trotter algorithm.
 *
 * INPUT:  an integer n with 1 <= n <= 25
 * OUTPUT: "There are x permutations of the set {1, 2, ..., n}:" where x = n!
 *         followed by a list of all permutations, one per line.
 */

#include <iostream>
#include <vector>
using namespace std;

// Directions used to track which way each element is "looking"
const int LEFT = -1;
const int RIGHT = 1;

// Computes n! as an unsigned long long.
// NOTE: this overflows for n >= 21 (20! is the largest factorial that
// fits in 64 bits). The assignment allows n up to 25, but at that size
// both the permutation count (25! ~ 1.55 x 10^25) and the number of
// permutations to print are far beyond what any program can actually
// generate or display, so this is really only practical for small n.
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Prints one permutation, values separated by spaces.
void printPermutation(const vector<int>& values) {
    for (size_t i = 0; i < values.size(); i++) {
        cout << values[i];
        if (i != values.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

// Returns the index of an element if it is mobile (its direction points
// toward a smaller adjacent element), or -1 if that element is not mobile.
bool isMobile(const vector<int>& values, const vector<int>& directions, int i) {
    int neighborIndex = i + directions[i];
    if (neighborIndex < 0 || neighborIndex >= (int)values.size()) {
        return false; // pointing off the end of the array
    }
    return values[i] > values[neighborIndex];
}

// Finds the index of the largest mobile element.
// Returns -1 if no element is mobile.
int findLargestMobile(const vector<int>& values, const vector<int>& directions) {
    int largestIndex = -1;
    for (int i = 0; i < (int)values.size(); i++) {
        if (isMobile(values, directions, i)) {
            if (largestIndex == -1 || values[i] > values[largestIndex]) {
                largestIndex = i;
            }
        }
    }
    return largestIndex;
}

// Generates and prints all permutations of {1, 2, ..., n} using
// the Johnson-Trotter algorithm.
void johnsonTrotter(int n) {
    vector<int> values(n);
    vector<int> directions(n, LEFT); // everyone starts pointing left

    for (int i = 0; i < n; i++) {
        values[i] = i + 1;
    }

    printPermutation(values); // print the initial permutation: 1 2 ... n

    int k = findLargestMobile(values, directions);
    while (k != -1) {
        int neighborIndex = k + directions[k];

        // Swap the largest mobile element with the neighbor it points to
        swap(values[k], values[neighborIndex]);
        swap(directions[k], directions[neighborIndex]);

        // Reverse the direction of every element larger than the one
        // that was just moved (now sitting at neighborIndex)
        int movedValue = values[neighborIndex];
        for (int i = 0; i < n; i++) {
            if (values[i] > movedValue) {
                directions[i] = -directions[i];
            }
        }

        printPermutation(values);
        k = findLargestMobile(values, directions);
    }
}

int main() {
    int n;
    cout << "Enter n (1 <= n <= 25): ";
    cin >> n;

    if (n < 1 || n > 25) {
        cout << "Error: n must be between 1 and 25." << endl;
        return 1;
    }

    unsigned long long x = factorial(n);
    cout << "There are " << x << " permutations of the set {1, 2, ..., " << n << "}:" << endl;

    johnsonTrotter(n);

    return 0;
}
