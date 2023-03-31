#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    stack<int> arr;
    int n;
    cin >> n;

    while (n--) {
        string str;
        cin >> str;
        if (str == "push") {
            int tmp;
            cin >> tmp;
            arr.push(move(tmp));
        }
        else if (str == "pop") {
            if (arr.size() == 0) cout << "-1" << "\n";
            else {
                cout << arr.top() << "\n";
                arr.pop();
            }
        }
        else if (str == "size") {
            cout << arr.size() << "\n";
        }
        else if (str == "empty") {
            if (arr.empty()) cout << "1" << "\n";
            else cout << "0" << "\n";
        }
        else {
            if (arr.size() == 0) cout << "-1" << "\n";
            else cout << arr.top() << "\n";
        }
    }
}