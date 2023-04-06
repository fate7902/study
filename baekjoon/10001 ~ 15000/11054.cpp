#include <iostream>
using namespace std;

int value[1001]{};
int dp[1001]{};
int rdp[1001]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i) cin >> value[i];

	for (int i = 1; i <= n; ++i) {
		dp[i] = 1;
		for (int j = 1; j < i; ++j) {
			if (value[j] < value[i]) dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
		}
	}

	for (int i = n; i > 0; --i) {
		rdp[i] = 1;
		for (int j = n; j > i; --j) {
			if (value[j] < value[i]) rdp[i] = rdp[i] > rdp[j] + 1 ? rdp[i] : rdp[j] + 1;
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; ++i) {
		answer = answer > dp[i] + rdp[i] - 1 ? answer : dp[i] + rdp[i] - 1;
	}
	cout << answer;
}