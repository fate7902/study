#include <iostream>
#include <set>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	set<string> arr;
	int n;
	cin >> n;

	int answer = 0;
	while (n--) {
		string str;
		cin >> str;
		if (str == "ENTER") {
			answer += arr.size();
			arr.clear();
		}
		else arr.emplace(str);
	}
	answer += arr.size();
	cout << answer;
}