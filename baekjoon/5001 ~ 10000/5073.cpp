#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	while (1) {
		int a, b, c;
		int len = 0, sum = 0;
		cin >> a >> b >> c;		

		len = max(a, b);
		len = max(len, c);
		sum = a + b + c - len;

		if (a + b + c == 0) break;
		if (sum <= len) cout << "Invalid\n";
		else if (a == b && b == c) cout << "Equilateral\n";
		else if (a == b || b == c || a == c) cout << "Isosceles\n";
		else cout << "Scalene\n";
	}
}