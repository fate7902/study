#include <iostream>
using namespace std;

long long int gcd(long long int a, long long int b) {
	if (a % b == 0) {
		return b;
	}
	return gcd(b, a % b);
}

int main() {
	long long int a, b;
	cin >> a >> b;
	cout << a * b / gcd(a, b);
}