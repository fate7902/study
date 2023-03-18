#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, temp, sum = 0;
    cin >> n >> m;
    arr.emplace_back(0);
    for (int i = 0; i < n; i++) {
        cin >> temp;
        sum += temp;
        arr.emplace_back(sum);
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << arr[b] - arr[a - 1] << "\n";
    }
}