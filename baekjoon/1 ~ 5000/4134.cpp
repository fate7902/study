#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		long long int tmp;
		cin >> tmp;

		if (tmp < 3) {
			cout << "2\n";
			continue;
		}

		for (long long int a = tmp; ; ++a) {
			int cnt = 1;
			if (a % 2 == 0) continue;
			for (long long int b = 3; b*b <= a; ++b) {
				if (a % b == 0) {
					cnt++;
					break;
				}
			}
			if (cnt == 1) {				
				cout << a << "\n";
				break;
			}
		}
	}
}