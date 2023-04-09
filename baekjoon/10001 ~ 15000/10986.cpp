#include <iostream>
using namespace std;

long long int arr[1000]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    long long int sum = 0, cnt = 0;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        sum += tmp;
        arr[sum % m]++;
        if (sum % m == 0) cnt++;
    }

    for (int i = 0; i < m; ++i) {
        if (arr[i] < 2) continue;
        cnt += (arr[i] * (arr[i] - 1) / 2);
    }

    cout << cnt;
}