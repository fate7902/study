#include <iostream>
#include <vector>
using namespace std;

int input[1000]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> input[i];
	}

	vector<int> arr;
	arr.emplace_back(1001);
	for (int i = n - 1; i >= 0; --i) {		
		if (arr.back() < input[i]) {
			arr.emplace_back(input[i]);
		}
		else {
			auto iter = lower_bound(arr.begin(), arr.end(), input[i]);
			*iter = input[i];
		}
	}
	cout << arr.size();
}