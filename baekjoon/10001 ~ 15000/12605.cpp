#include <iostream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	cin.ignore();

	for (int i = 1; i <= n; ++i) {
		stack<string> s;
		string str;
		getline(cin, str);

		stringstream ss(str);		
		string word;
		while (ss >> word) {
			s.emplace(word);
		}

		cout << "Case #" << i << ": ";
		while (!s.empty()) {
			cout << s.top() << " ";
			s.pop();
		}
		cout << "\n";
	}	
}