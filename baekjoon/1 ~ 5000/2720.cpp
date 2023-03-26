#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t; 
	cin >> t;
	
	while (t--) {
		int c;
		cin >> c;
		cout << c / 25 << " ";
		c %= 25;
		cout << c / 10 << " ";
		c %= 10;
		cout << c / 5 << " ";
		c %= 5;
		cout << c / 1 << "\n";
	}
}