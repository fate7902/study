#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    stack<int> arr;
    int k;
    cin >> k;

    while (k--) {
        int tmp;
        cin >> tmp;
        if (tmp != 0) arr.push(tmp);
        else arr.pop();
    }

    int answer = 0;
    while (arr.size()) {
        answer += arr.top();
        arr.pop();
    }
    cout << answer;
}