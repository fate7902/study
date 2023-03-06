#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> arr;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }else return a.second < b.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int case_num, x, y;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> x >> y;
        arr.emplace_back(make_pair(x, y));
    }
    stable_sort(arr.begin(), arr.end(), cmp);

    for (const auto& p : arr) {
        cout << p.first << " " << p.second << "\n";
    }
}