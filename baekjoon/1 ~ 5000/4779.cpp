#include <iostream>
#include <string>
using namespace std;

string Cantor(string str, int n) {
	if (n == 0) return str;
	string tmp(str);
	int len = str.size();
	for (int i = 0; i < len; ++i) {
		str += " ";
	}
	str += tmp;
	return Cantor(str, n - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	while (cin >> n) {
		cout << Cantor("-", n) << "\n";
	}
}