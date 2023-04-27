#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long int a[2]{};
    for (int i = 0; i < 2; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        s1 += s2;
        a[i] = stol(s1);
    }
    cout << a[0] + a[1];
}