#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> num;
        while (n--) {
            int tmp;
            cin >> tmp;
            num.emplace_back(tmp);
        }
        sort(num.begin(), num.end());

        int m;
        cin >> m;
        while (m--) {
            int tmp;
            cin >> tmp;
            if (binary_search(num.begin(), num.end(), tmp) == true) cout << "1\n";
            else cout << "0\n";
        }        
    }
}