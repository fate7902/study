#include <iostream>
#include <set>
using namespace std;

struct comp {
	bool operator() (const string& a, const string& b) const {
		return a > b;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	set<string, comp> arr;
	int n;
	cin >> n;

	while (n--) {
		string name, status;
		cin >> name >> status;
		if (status == "enter") arr.emplace(name);
		else arr.erase(name);
	}	
	
	for (const auto& p : arr) {
		cout << p << "\n";
	}
}