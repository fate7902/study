#include <iostream>
using namespace std;

long long int arr[10001]{};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int k, n;
	long long int small = 1;
	long long int large = 0;
	cin >> k >> n;
	for (int i = 1; i <= k; ++i) {
		cin >> arr[i];
		large = large > arr[i] ? large : arr[i];
	}

	while (small <= large) {
		long long int cnt = 0;
		long long int mid = (small + large) / 2;
		for (int i = 1; i <= k; ++i) {
			cnt += (arr[i] / mid);
			if (cnt >= n) break;
		}
		if (cnt >= n) small = mid + 1;
		else large = mid - 1;
	}
	cout << large;
}