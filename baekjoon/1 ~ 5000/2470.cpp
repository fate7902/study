#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; ++i) cin >> vec[i];
	sort(vec.begin(), vec.end());

	int s = 0, e = n - 1;
	int min = INT_MAX;
	pair<int, int> pos;
	while (s < e) {
		int tmp = vec[s] + vec[e];
		if (abs(min) > abs(tmp)) {
			min = tmp;
			pos = { s, e };
			if (min == 0) break;
		}
		if (tmp < 0) s++;
		else e--;
	}
	if (vec[pos.first] < vec[pos.second]) cout << vec[pos.first] << " " << vec[pos.second];
	else cout << vec[pos.second] << " " << vec[pos.first];
}