#include <iostream>
#include <queue>
#include <cstdlib>
using namespace std;

struct cmp {
    bool operator()(int a, int b) {
        if (abs(a) == abs(b)) return a > b;
        return abs(a) > abs(b);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, cmp> q;
    while (n--) {
        int tmp;
        cin >> tmp;

        if (tmp == 0) {
            if (q.empty()) cout << "0\n";
            else {
                cout << q.top() << "\n";
                q.pop();
            }
        }
        else {
            q.emplace(tmp);
        }
    }
}