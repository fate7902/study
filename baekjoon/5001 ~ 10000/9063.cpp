#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int minX = 10001, maxX = -10001, minY = 10001, maxY = -10001;
	int n;

	cin >> n;

	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		minX = min(x, minX);
		maxX = max(x, maxX);
		minY = min(y, minY);
		maxY = max(y, maxY);
	}

	cout << (maxX - minX) * (maxY - minY);
}