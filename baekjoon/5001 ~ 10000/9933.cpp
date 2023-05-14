#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	map<string, int> m;
	while(n--){
		string str;
		cin >> str;
		m[str]++;
		reverse(str.begin(), str.end());
		m[str]++;
	}

	for (auto& a : m) {
		if (a.second == 2) {
			cout << a.first.size() << " " << a.first[a.first.size() / 2];
			break;
		}
	}
}