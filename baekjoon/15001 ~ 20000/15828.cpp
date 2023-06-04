#include <iostream>
#include <queue>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	queue<int> q;
	while (true) {
		int tmp;
		cin >> tmp;
		if (tmp == -1) break;
		else if (tmp == 0) q.pop();
		else if (q.size() < n) {
			q.emplace(tmp);
		}
	}

	if (q.empty()) cout << "empty";
	else {
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop();
		}
	}
}