#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.emplace(i);
    }

    cout << "<";
    while (q.empty() == false) {
        for (int i = 1; i < k; ++i) {
            q.emplace(q.front());
            q.pop();
        }
        cout << q.front();
        q.pop();
        if (q.empty() == false) cout << ", ";
    }
    cout << ">";
}