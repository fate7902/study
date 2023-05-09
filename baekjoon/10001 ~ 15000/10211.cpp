#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, max = -99999999;
        cin >> n;

        int* dp = new int[n + 1];
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) cin >> dp[i];

        for (int i = 1; i <= n; ++i) {
            if (dp[i - 1] >= 0) dp[i] += dp[i - 1];
            max = max > dp[i] ? max : dp[i];
        }
        delete[] dp;

        cout << max << "\n";
    }
}