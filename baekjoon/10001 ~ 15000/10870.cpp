#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n > 1) {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    return n;
}

int main() {
    int num;
    cin >> num;
    cout << fibonacci(num);
}