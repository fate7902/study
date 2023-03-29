#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	int** arr = new int*[n];
	for (int i = 0; i < n; ++i) {
		arr[i] = new int[i + 1];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			cin >> arr[i][j];
		}
	}

	for (int i = n - 2; i >= 0; --i) {
		for (int j = 0; j <= i; ++j) {
			arr[i][j] += arr[i + 1][j] > arr[i + 1][j + 1] ? arr[i + 1][j] : arr[i + 1][j + 1];
		}
	}

	cout << arr[0][0];

	for (int i = 0; i < n; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
}