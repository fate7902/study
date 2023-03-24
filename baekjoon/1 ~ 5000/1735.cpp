#include <iostream>
using namespace std;

int gcd(int a, int b) {
	if (a % b == 0) {
		return b;
	}
	return gcd(b, a % b);
}

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	int lcm = b * d / gcd(b, d);
	int bunja = a * (lcm / b) + c * (lcm / d);
	int bunmo = lcm;

	while (true) {
		int tmp = gcd(bunja, bunmo);
		if (tmp == 1) break;
		else {
			bunja /= tmp;
			bunmo /= tmp;
		}
	}

	cout << bunja << " " << bunmo;
}