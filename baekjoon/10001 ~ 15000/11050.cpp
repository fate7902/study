#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int result = 1;

    for (int i = n; i > n - k; --i) {
        result *= i;
    }

    for (int i = 1; i <= k; ++i) {
        result /= i;
    }

    cout << result << endl;
}