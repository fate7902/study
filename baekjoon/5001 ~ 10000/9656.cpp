#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	if (n % 4 == 1 || n % 4 == 3) cout << "CY";
	else cout << "SK";
}