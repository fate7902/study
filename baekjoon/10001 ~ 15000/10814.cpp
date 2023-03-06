#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, string>> arr;

bool cmp(pair<int, string> a, pair<int, string> b) {
    return a.first < b.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int case_num, num;
    string str;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> num >> str;
        arr.emplace_back(make_pair(num, str));
    }

    stable_sort(arr.begin(), arr.end(), cmp);

    for (const auto& p : arr) {
        cout << p.first << " " << p.second << "\n";
    }
}