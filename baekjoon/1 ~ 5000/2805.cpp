#include <iostream>
using namespace std;

int arr[1000001]{};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	long long int large = 0;
	long long int small = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		large = large > arr[i] ? large : arr[i];		
	}

	while (small <= large) {
		long long int cnt = 0;
		long long int mid = (small + large) / 2;

		for (int i = 1; i <= n; ++i) {
			if (arr[i] > mid) cnt += (arr[i] - mid);
			if (cnt >= m) break;
		}
		if (cnt >= m) small = mid + 1;
		else large = mid - 1;
	}
	cout << large;
}