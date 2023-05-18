#include <iostream>
using namespace std;

char arr[64][64]{};

void quadtree(int n, int x, int y) {
	bool bwhite = false;
	bool bblue = false;

	for (int i = x; i < x + n; ++i) {
		for (int j = y; j < y + n; ++j) {
			if (arr[i][j] == '0') bwhite = true;
			else bblue = true;
			if (bwhite && bblue) break;
		}
		if (bwhite && bblue) break;
	}

	if (bwhite && bblue) {
		cout << "(";
		quadtree(n / 2, x, y);
		quadtree(n / 2, x, y + n / 2);
		quadtree(n / 2, x + n / 2, y);
		quadtree(n / 2, x + n / 2, y + n / 2);
		cout << ")";
	}
	else if (bwhite) cout << "0";	
	else cout << "1";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> arr[i][j];
		}
	}

	quadtree(n, 0, 0);
}