#include <iostream>
#include <set>
using namespace std;

int main() {
	set<string> arr{ "ChongChong" };
	int n;
	cin >> n;

	while (n--) {
		string a, b;
		cin >> a >> b;
		if (arr.find(a) != arr.end() || arr.find(b) != arr.end()) {
			arr.insert(b);
			arr.insert(a);
		}		
	}
	cout << arr.size();
}