#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<pair<int, int>> vec(n);
	for (int i = 0; i < n; ++i) cin >> vec[i].first >> vec[i].second;

	sort(vec.begin(), vec.end());
	vector<int> tmp;
	tmp.emplace_back(501);
	for (int i = 0; i < n; ++i) {
		if (tmp.back() < vec[i].second) tmp.emplace_back(vec[i].second);
		else {
			auto iter = lower_bound(tmp.begin(), tmp.end(), vec[i].second);
			*iter = vec[i].second;
		}
	}	
	cout << vec.size() - tmp.size();
}