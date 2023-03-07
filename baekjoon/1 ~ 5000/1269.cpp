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

    vector<int> arr(n);    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];        
    }
    sort(arr.begin(), arr.end());

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int temp;
        cin >> temp;
        if (binary_search(arr.begin(), arr.end(), temp) == 1) {
            cnt++;
        }
    }    

    cout << n + m - 2 * cnt;
}