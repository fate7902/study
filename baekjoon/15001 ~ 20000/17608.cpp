#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    stack<int> s;
    while (n--) {
        int tmp;
        cin >> tmp;
        s.emplace(tmp);
    }

    int cnt = 0, max = 0;
    while (s.empty() == false) {
        if (s.top() > max) {
            max = s.top();
            cnt++;
        }
        s.pop();
    }
    cout << cnt;
}