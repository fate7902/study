#include <iostream>
#include <string>
using namespace std;

int dp[1001][1001]{};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string a, b;
	cin >> a >> b;
	
	int lenA = a.size();
	int lenB = b.size();
	for (int i = 0; i < lenA; ++i) {
		for (int j = 0; j < lenB; ++j) {
			if (a[i] == b[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
			else dp[i + 1][j + 1] = dp[i][j + 1] > dp[i + 1][j] ? dp[i][j + 1] : dp[i + 1][j];
		}
	}

	cout << dp[lenA][lenB];
}