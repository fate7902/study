#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        queue<pair<int, int>> arr;
        priority_queue<int> q;
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            arr.emplace(i, tmp);
            q.emplace(tmp);
        }
        
        int cnt = 0;
        while (!q.empty()) {
            if (q.top() == arr.front().second) {
                cnt++;
                if (arr.front().first == m) {
                    cout << cnt << "\n";
                    break;
                }
                else arr.pop();
                q.pop();
            }
            else {
                arr.emplace(arr.front());
                arr.pop();
            }
        }
    }
}