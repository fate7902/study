#include <iostream>
using namespace std;

int main() {
	int a1, a0, c, n0;
	cin >> a1 >> a0 >> c >> n0;
	
	auto f = [a1, a0](int n) { return a1 * n + a0; };
	auto g = [](int n) { return n; };

	if (c >= a1 && f(n0) <= c * g(n0)) cout << "1";
	else cout << "0";
}