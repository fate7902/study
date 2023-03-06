#include <iostream>
using namespace std;

int factorial(int n) {
    if (n > 1) return factorial(n - 1) * n;
    return 1;
}

int main() {
    int num;
    cin >> num;
    cout << factorial(num);
}