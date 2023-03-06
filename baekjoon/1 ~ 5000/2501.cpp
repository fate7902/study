#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    vector<int> list;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            list.emplace_back(i);
        }
    }
    sort(list.begin(), list.end());
    if (list.size() < k) cout << "0";
    else cout << list[k - 1];
}