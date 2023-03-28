#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	int arr[1000][3]{};
	for (int i = 0; i < n; ++i) {
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
	}
	
	int sum[1000][3]{};
	sum[0][0] = arr[0][0];
	sum[0][1] = arr[0][1];
	sum[0][2] = arr[0][2];
	for (int i = 1; i < n; ++i) {
		sum[i][0] = min(sum[i - 1][1], sum[i - 1][2]) + arr[i][0];
		sum[i][1] = min(sum[i - 1][0], sum[i - 1][2]) + arr[i][1];
		sum[i][2] = min(sum[i - 1][0], sum[i - 1][1]) + arr[i][2];
	}

	cout << min(min(sum[n - 1][0], sum[n - 1][1]), sum[n - 1][2]);
}