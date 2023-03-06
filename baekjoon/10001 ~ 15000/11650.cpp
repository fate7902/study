#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> arr;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }else return a.first < b.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int case_num, x, y;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> x >> y;
        arr.emplace_back(make_pair(x, y));
    }
    sort(arr.begin(), arr.end(), cmp);

    for (const auto& p : arr) {
        cout << p.first << " " << p.second << "\n";
    }
}