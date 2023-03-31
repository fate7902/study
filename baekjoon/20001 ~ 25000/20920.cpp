#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    map<string, int> arr;
    int n, m;
    cin >> n >> m;

    while (n--) {
        string str;
        cin >> str;
        if (str.size() >= m) {
            arr[str]++;
        }
    }

    vector<pair<string, int>> vec(arr.begin(), arr.end());
    sort(vec.begin(), vec.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second == b.second) {
                if (a.first.size() == b.first.size()) return a.first < b.first;
                return a.first.size() > b.first.size();
            }
            return a.second > b.second;
        });
    for (const auto& elem : vec) {
        cout << elem.first << "\n";
    }
}
