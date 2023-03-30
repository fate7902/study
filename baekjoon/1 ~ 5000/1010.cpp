#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;

	while (t--) {
		int n, m, answer = 1;
		cin >> n >> m;
		int tmp = 1;
		for (int i = m; i > m - n; --i) {
			answer *= i;
			answer /= tmp++;
		}
		cout << answer << "\n";
	}
}