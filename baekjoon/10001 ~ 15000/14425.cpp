#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;    
    vector<string> arr(n);    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];        
    }
    sort(arr.begin(), arr.end());

    int answer = 0;
    for (int i = 0; i < m; i++) {
        string str;
        cin >> str;
        if (binary_search(arr.begin(), arr.end(), str) == 1) answer++;
    }

    cout << answer;
}