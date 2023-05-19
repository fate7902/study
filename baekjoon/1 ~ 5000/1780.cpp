#include <iostream>
using namespace std;

short arr[2187][2187]{};
int cnt[3]{};

void quadtree(int n, int x, int y) {
	bool bminus = false;
	bool bzero = false;
	bool bplus = false;

	for (int i = x; i < x + n; ++i) {
		for (int j = y; j < y + n; ++j) {
			if (arr[i][j] == -1) bminus = true;
			else if (arr[i][j] == 0) bzero = true;
			else bplus = true;
			if ((bminus && bzero) || (bminus && bplus) || (bzero && bplus)) break;
		}
		if ((bminus && bzero) || (bminus && bplus) || (bzero && bplus)) break;
	}

	if ((bminus && bzero) || (bminus && bplus) || (bzero && bplus)) {
		quadtree(n / 3, x, y);
		quadtree(n / 3, x, y + n / 3);
		quadtree(n / 3, x + n / 3, y);
		quadtree(n / 3, x + n / 3, y + n / 3);
		quadtree(n / 3, x, y + n / 3 * 2);
		quadtree(n / 3, x + n / 3 * 2, y);
		quadtree(n / 3, x + n / 3 * 2, y + n / 3 * 2);
		quadtree(n / 3, x + n / 3, y + n / 3 * 2);
		quadtree(n / 3, x + n / 3 * 2, y + n / 3);
	}
	else if (bminus) cnt[0]++;
	else if (bzero) cnt[1]++;
	else cnt[2]++;
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
	cout << cnt[0] << "\n" << cnt[1] << "\n" << cnt[2];
}