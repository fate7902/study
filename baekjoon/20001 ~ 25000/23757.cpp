#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    priority_queue<int> q;
    while (n--) {
        int tmp;
        cin >> tmp;
        q.emplace(tmp);
    }

    bool flag = true;
    while (m--) {
        int max = q.top();
        int tmp;
        cin >> tmp;

        if (flag == false) continue;

        if (max >= tmp) {
            max -= tmp;
            q.pop();
            if (max != 0) q.emplace(max);
        }
        else flag = false;
    }

    if (flag == true) cout << "1";
    else cout << "0";
}