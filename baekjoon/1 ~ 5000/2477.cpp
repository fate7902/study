#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int k;
    cin >> k;

    vector<pair<int, int>> list;
    int cnt[5] = { 0 };
    for (int i = 0; i < 6; ++i) {
        int dir, len;
        cin >> dir >> len;
        list.emplace_back(dir, len);
        cnt[dir]++;
    }

    vector<int> h, v;
    for (const auto& l : list) {
        if (l.first == 1 || l.first == 2) {
            h.emplace_back(l.second);
        }
        else {
            v.emplace_back(l.second);
        }
    }

    int h_max = *max_element(h.begin(), h.end());
    int v_max = *max_element(v.begin(), v.end());
    int big_area = h_max * v_max;

    vector<int> pp;
    for (int i = 1; i < 5; ++i) {
        if (cnt[i] == 1) {
            auto it = find_if(list.begin(), list.end(), [i](const auto& l) {
                return l.first == i;
                });
            pp.emplace_back(distance(list.begin(), it));
        }
    }

    int small_area = list[(pp[0] + 3) % 6].second * list[(pp[1] + 3) % 6].second;
    cout << (big_area - small_area) * k << endl;
    return 0;
}