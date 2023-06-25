#include <iostream>
#include <algorithm>
using namespace std;

int arr[100001]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, x;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	cin >> x;

	int answer = 0;
	sort(arr, arr + n + 1);
	int s = 1, e = n;
	while (s < e) {
		int tmp = arr[s] + arr[e];
		if (tmp == x) { answer++; s++; }
		else if (tmp < x) s++;
		else e--;
	}
	cout << answer;
}