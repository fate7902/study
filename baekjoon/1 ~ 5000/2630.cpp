#include <iostream>
using namespace std;

int arr[128][128]{};
int white_cnt = 0;
int blue_cnt = 0;

void quadtree(int n, int x, int y) {
	bool bwhite = false;
	bool bblue = false;

	for (int i = x; i < x + n; ++i) {
		for (int j = y; j < y + n; ++j) {
			if (arr[i][j] == 0) bwhite = true;
			else bblue = true;
			if (bwhite && bblue) break;
		}
		if (bwhite && bblue) break;
	}

	if (bwhite && bblue) {
		quadtree(n / 2, x, y);
		quadtree(n / 2, x, y + n / 2);
		quadtree(n / 2, x + n / 2, y);
		quadtree(n / 2, x + n / 2, y + n / 2);
	}
	else if (bwhite) white_cnt++;
	else blue_cnt++;
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
	cout << white_cnt << "\n" << blue_cnt;
}