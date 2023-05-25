#include <iostream>
using namespace std;

int arr[1001]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	arr[1] = arr[3] = arr[4] = 1;
	arr[2] = 0;

	for (int i = 5; i <= n; ++i) {
		if (arr[i - 1] + arr[i - 3] + arr[i - 4] < 3) arr[i] = 1;
		else arr[i] = 0;
	}

	if (arr[n] == 1) cout << "SK";
	else cout << "CY";
}