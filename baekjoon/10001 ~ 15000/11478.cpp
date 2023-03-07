#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
	string str;
	cin >> str;

	unordered_set<string> list;
	for (int i = 1; i <= str.size(); ++i) {
		int p = 0;
		while (p + i <= str.size()) {
			string tmp = str.substr(p++, i);
			list.insert(tmp);
		}
	}
	cout << list.size();
}