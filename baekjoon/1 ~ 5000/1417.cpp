#include <iostream>
#include <queue>
using namespace std;

struct cmp {
	bool operator()(pair<int, int> a, pair<int, int> b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second < b.second;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	int num;
	for (int i = 1; i <= n; ++i) {
		int tmp;
		cin >> tmp;
		if (i == 1) num = tmp;
		pq.emplace(i, tmp);
	}

	int cnt = 0;
	while (true) {
		auto a = pq.top();
		if (a.first == 1 || a.second < num) {
			cout << cnt;
			break;
		}
		num++;
		cnt++;
		a.second--;
		pq.pop();
		pq.emplace(a);
	}
}