#include <iostream>
using namespace std;

int sum[100001]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        int tmp;
        cin >> tmp;
        sum[i] = sum[i - 1] + tmp;
    }

    int max = -10000001;
    for (int i = 0; i <= n - k; ++i) max = max > sum[k + i] - sum[i] ? max : sum[k + i] - sum[i];

    cout << max;
}