#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n; 
	cin >> n;

	cout << (long long int)pow(pow(2, n) + 1, 2);
}