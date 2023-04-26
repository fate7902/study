#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    while (n--) {
        string str;
        cin >> str;
        reverse(begin(str), end(str));
        cout << str << "\n";
    }
}