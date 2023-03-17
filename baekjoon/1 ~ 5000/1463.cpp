#include <iostream>
#include<cstring>
#include <algorithm>
using namespace std;

int counting(int dp[], int n) {
    dp[0] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        if (i % 3 == 0) dp[i] = min(dp[i], dp[i / 3] + 1);
        if (i % 2 == 0) dp[i] = min(dp[i], dp[i / 2] + 1);
    }

    return dp[n];
}

int main() {
    int n;
    cin >> n;
    int* dp = new int[n + 1];
    memset(dp, 0, sizeof(int) * (n + 1));    
    cout << counting(dp, n);
    delete[] dp;
}