#include <iostream>
#include <string>
using namespace std;

int main() {
	string n;
	int b, answer = 0;
	cin >> n >> b;

	int value = 1;
	for (int i = n.size() - 1; i >= 0; --i) {
		if (n[i] >= 65) {
			answer += ((n[i] - 55) * value);
		}
		else {
			answer += ((n[i] - '0') * value);
		}
		value *= b;
	}
	cout << answer;
}