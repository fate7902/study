#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.emplace(i);
    }

    while (q.empty() == false) {
        cout << q.front() << " ";
        q.pop();
        if (q.empty() == false) {
            q.emplace(q.front());
            q.pop();
        }
    }
}