#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, a;
    cin >> n;    
    for (int i = 0; i < n; i++) {
        cin >> a;
        arr.emplace_back(a);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a;
        if (binary_search(arr.begin(), arr.end(), a) == 0) cout << "0" << "\n";
        else cout << "1" << "\n";
    }
}