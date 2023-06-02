#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	long long int n, m;
	cin >> n >> m;

	cout << ((n - 1) % (m + 1) == 0 ? "Can't win" : "Can win");
}