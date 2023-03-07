#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<pair<int, int>> arr;
    int n, x, y;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        arr.emplace_back(make_pair(x, y));
    }

    for (int i = 0; i < arr.size(); i++) {
        int cnt = 0;
        for (int j = 0; j < arr.size(); j++) {
            if (i != j) {
                if (arr[i].first < arr[j].first && arr[i].second < arr[j].second) {
                    cnt++;
                }
            }
        }
        cout << cnt + 1 << " ";
    }
}