#include <iostream>
using namespace std;

int dp[1001]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	dp[1] = dp[3] = 0;
	dp[2] = dp[4] = 1;

	for (int i = 5; i <= n; ++i) {
		if (dp[i - 1] + dp[i - 3] + dp[i - 4] != 3) dp[i] = 1;
		else dp[i] = 0;
	}

	if (dp[n] == 1) cout << "SK";
	else cout << "CY";
}