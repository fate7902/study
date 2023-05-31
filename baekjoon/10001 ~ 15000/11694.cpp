#include <iostream>
using namespace std;

int arr[100]{};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, ret = 0, cnt = 0;
	cin >> n;

	for (int i = 0; i < n; ++i) {		
		cin >> arr[i];
		ret ^= arr[i];
		if (arr[i] == 1) cnt++;
	}

	if (cnt == 0) cout << (ret == 0 ? "cubelover" : "koosaga");
	else {
		if(cnt == n) cout << (ret % 2 == 0 ? "koosaga" : "cubelover");
		else if (cnt % 2 == 1) cout << (ret == 0 ? "cubelover" : "koosaga");
		else {
			for (auto& a : arr) {
				if (a != 1) {
					a = 1;
					break;
				}
			}
			ret = 0;
			for (const auto& a : arr) {
				ret ^= a;
			}
			cout << (ret == 0 ? "cubelover" : "koosaga");
		}
	}	
}