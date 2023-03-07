#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> arrA(n);
    for (int i = 0; i < n; i++) {
        cin >> arrA[i];
    }
    sort(arrA.begin(), arrA.end());

    vector<string> arrB;
    for (int i = 0; i < m; i++) {
        string str;
        cin >> str;
        if (binary_search(arrA.begin(), arrA.end(), str) == 1) {
            arrB.emplace_back(str);
        }
    }
    sort(arrB.begin(), arrB.end());

    cout << arrB.size() << "\n";
    for (int i = 0; i < arrB.size(); i++) {
        cout << arrB[i] << "\n";
    }
}