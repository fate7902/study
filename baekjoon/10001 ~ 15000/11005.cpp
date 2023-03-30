#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	int n, b;
	cin >> n >> b;

	string s;
	while (n > 0) {
		int tmp = n % b;
		if (tmp >= 10) s += (tmp + 55);
		else s += to_string(tmp);
		n /= b;
	}
	reverse(begin(s), end(s));
	cout << s;
}