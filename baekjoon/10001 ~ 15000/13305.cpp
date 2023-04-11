#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n - 1; ++i) cin >> vec[i].second;
    for (int i = 0; i < n; ++i) cin >> vec[i].first;

    long long int answer = 0;
    long long int price = vec[0].first;
    int pos = 0;
    for (int i = 1; i < n; ++i) {
        if (vec[i].first >= price && i != n - 1) continue;
        long long int len = 0;
        for (int j = pos; j < i; ++j) {
            len += vec[j].second;
        }
        answer += (price * len);
        price = vec[i].first;
        pos = i;
    }

    cout << answer;
}