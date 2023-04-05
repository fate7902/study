#include <iostream>
using namespace std;

constexpr int mod = 1000000000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	int arr[101][11]{};
	arr[1][0] = 0;
	for (int i = 1; i <= 9; ++i) {
		arr[1][i] = 1;
	}

	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j <= 9; ++j) {
			if (j == 0) arr[i][j] = arr[i - 1][1] % mod;
			else if(j == 9) arr[i][j] = arr[i - 1][8] % mod;
			else arr[i][j] = (arr[i - 1][j - 1] + arr[i - 1][j + 1]) % mod;
		}
	}

	int answer = 0;
	for (int i = 0; i <= 9; ++i) answer = (answer + arr[n][i]) % mod;

	cout << answer;
}