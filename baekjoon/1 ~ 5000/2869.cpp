#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    while (true) {
        if (c > a) {
            int d = a - b;
            if ((c - a) % d == 0) {
                cout << (c - a) / d + 1;
            }
            else {
                cout << (c - a) / d + 2;
            }
            break;
        }
        else {
            cout << "1";
            break;
        }
    }
}