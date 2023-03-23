#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a, b, c;
	int len = 0, sum = 0;
	cin >> a >> b >> c;

	len = max(a, b);
	len = max(len, c);
	sum = a + b + c - len;

	if (len >= sum) len = sum - 1;

	cout << sum + len;
}