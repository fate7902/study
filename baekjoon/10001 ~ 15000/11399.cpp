#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;

int main() {
    int n, a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        arr.emplace_back(a);
    }
    sort(arr.begin(), arr.end());
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (arr[i] * (n - i));
    }
    cout << sum;
}