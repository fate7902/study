#include <iostream>
#include <algorithm>
using namespace std;

int value[10001]{};
int arr[10001][3]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i) cin >> value[i];

	arr[1][0] = arr[1][2] = 0;
	arr[1][1] = value[1];
	for (int i = 2; i <= n; ++i) {
		arr[i][0] = max(max(arr[i - 1][0], arr[i - 1][1]), arr[i - 1][2]);
		arr[i][1] = arr[i - 1][0] + value[i];
		arr[i][2] = arr[i - 1][1] + value[i];
	}

	cout << max(max(arr[n][0], arr[n][1]), arr[n][2]);
}