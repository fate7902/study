#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	int arr[100000]{};
	int answer = -1000000000;
	for (int i = 0; i < n; ++i) {		
		cin >> arr[i];
		if (i > 0) {
			if (arr[i - 1] > 0) arr[i] += arr[i - 1];
		}		
		answer = arr[i] > answer ? arr[i] : answer;
	}
	cout << answer;
}