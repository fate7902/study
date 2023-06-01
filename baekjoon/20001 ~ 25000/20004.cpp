#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int a;
	cin >> a;

	for (int i = 1; i <= a; ++i) {
		if (30 % (i + 1) == 0) cout << i << "\n";
	}
}