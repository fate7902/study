#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, ret = 0;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		ret ^= tmp;
	}

	if (ret == 0)cout << "cubelover";
	else cout << "koosaga";
}