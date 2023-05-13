#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string a, b;
    char oper;
    cin >> a >> oper >> b;

    int len_a = a.size();
    int len_b = b.size();
    switch (oper) {
    case '+':
        if (len_a >= len_b) {
            a[len_a - len_b] = a[len_a - len_b] + 1;
            cout << a;
        }        
        else {
            b[len_b - len_a] = '1';
            cout << b;
        }
        break;
    case '*':
        for (int i = 1; i < len_b; ++i) {
            a += '0';
        }
        cout << a;
        break;
    }
}