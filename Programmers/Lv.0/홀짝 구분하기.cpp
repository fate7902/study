#include <iostream>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    cout << n << (n % 2 == 0 ? " is even" : " is odd");
}