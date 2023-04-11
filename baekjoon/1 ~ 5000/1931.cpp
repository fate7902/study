#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;    
    cin >> n;

    vector<pair<int, int>> vec(n);
    for(int i = 0; i < n; ++i) {
        cin >> vec[i].first >> vec[i].second;
    }
    sort(vec.begin(), vec.end(), cmp);

    int endT = vec[0].second, cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (vec[i].first >= endT) {
            cnt++;
            endT = vec[i].second;
        }
    }

    cout << cnt;
}