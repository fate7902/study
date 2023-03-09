#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(vector<int>& origin, vector<int>& oper, int pick, int n, int m) {
    if (pick == m) {
        for (const auto& a : oper) {
            cout << a << " ";
        }
        cout << "\n";
    }
    else {
        for (int i = 0; i < n; ++i) {
            if (find(oper.begin(), oper.end(), i + 1) == oper.end()) {
                if (oper.size() == 0 || origin[i] > oper.back()) {
                    oper.emplace_back(origin[i]);
                    dfs(origin, oper, pick + 1, n, m);
                    oper.erase(oper.end() - 1);
                }
            }
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n), tmp;
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    dfs(arr, tmp, 0, n, m);
}