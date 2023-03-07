#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {        
        cin >> arr[i];
    }
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    sort(arr.begin(), arr.end());

    cin >> m;
    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        cout << binary_search(arr.begin(), arr.end(), num) << " ";
    }
}