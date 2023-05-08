#include <iostream>
using namespace std;

int dp[11]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int max = 0;
    for (int i = 1; i <= 10; ++i) {
        int tmp;
        cin >> tmp;
        dp[i] = dp[i - 1] + tmp;
        if (dp[i] <= 100) max = i;
    }

    if (dp[max] == 100 || max == 10) cout << dp[max];
    else if (100 - dp[max] >= dp[max + 1] - 100) cout << dp[max + 1];
    else  cout << dp[max];
}