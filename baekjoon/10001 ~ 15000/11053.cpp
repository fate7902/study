#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<int> arr;
	arr.emplace_back(1001);
	for (int i = 1; i <= n; ++i) {
		int tmp;
		cin >> tmp;
		if (arr.back() < tmp) {
			arr.emplace_back(tmp);
		}
		else {
			auto iter = lower_bound(arr.begin(), arr.end(), tmp);
			*iter = tmp;
		}
	}
	cout << arr.size();
}