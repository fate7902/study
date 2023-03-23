#include <iostream>
using namespace std;

int main() {
	int a, b, c, d, e, f;	
	cin >> a >> b >> c >> d >> e >> f;

	auto g = [a, b, c](int x, int y) {return a * x + b * y == c; };
	auto h = [d, e, f](int x, int y) {return d * x + e * y == f; };

	for (int x = -999; x < 1000; ++x) {
		for (int y = -999; y < 1000; ++y) {
			if (g(x, y) != true) continue;
			if (h(x, y) == true) cout << x << " " << y;
		}
	}
}