#include <iostream>
#include <cmath>
using namespace std;

bool flag[1000001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
		
	flag[0] = flag[1] = true;
	for (int i = 2; i <= sqrt(1000000); i++) {
		if (flag[i] == true) continue;
		for (int j = i * i; j <= 1000000; j += i) {
			flag[j] = true;
		}
	}

	int t;
	cin >> t;

	while (t--) {
		int n, cnt = 0;
		cin >> n;

		for (int i = 0; i <= n / 2; ++i) {
			int x = i;
			int y = n - i;
			if (flag[x] == false && flag[y] == false) cnt++;
		}

		cout << cnt << "\n";
	}
}