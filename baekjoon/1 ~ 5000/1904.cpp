#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int arr[3];
	arr[0] = 1;
	arr[1] = arr[2] = 2;
	for (int i = 3; i <= n; ++i) {
		arr[2] = (arr[0] + arr[1]) % 15746;
		arr[0] = arr[1];
		arr[1] = arr[2];
	}
	if (n == 1) cout << arr[0];
	else cout << arr[2];
}