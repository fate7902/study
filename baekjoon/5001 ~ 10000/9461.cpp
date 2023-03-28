#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	long long int arr[101]{};
	arr[1] = arr[2] = arr[3] = 1;
	while (t--) {
		int n;
		cin >> n;
		if (arr[n] == 0) {
			for (int i = 4; i <= n; ++i) {
				if (arr[i] != 0) continue;
				arr[i] = (arr[i - 2] + arr[i - 3]);
			}
		}
		cout << arr[n] << "\n";
	}
}