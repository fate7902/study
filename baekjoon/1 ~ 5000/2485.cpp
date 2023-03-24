#include <iostream>
using namespace std;

int gcd(int a, int b) {
	if (a % b == 0) {
		return b;
	}
	return gcd(b, a % b);
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	int* dis = new int[n - 1];

	cin >> arr[0];
	for (int i = 1; i < n; ++i) {		
		cin >> arr[i];
		dis[i - 1] = arr[i] - arr[i - 1];
	}

	int g = dis[0];
	for (int i = 1; i < n - 1; ++i) {
		g = gcd(g, dis[i]);
	}
	cout << (arr[n - 1] - arr[0]) / g - (n - 1);

	delete[] arr, dis;
}