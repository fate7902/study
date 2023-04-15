#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    priority_queue<int> q;
    for (int i = 0; i < n * n; ++i) {
        int tmp;
        cin >> tmp;
        q.emplace(-tmp);
        if (q.size() > n) q.pop();
    }    

    cout << -q.top();
}