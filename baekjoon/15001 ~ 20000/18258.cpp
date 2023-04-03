#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    queue<int> arr;
    while (n--) {
        string str;
        cin >> str;
        if (str == "push") {
            int tmp;
            cin >> tmp;
            arr.emplace(tmp);
        }
        else if (str == "pop") {
            if (arr.size() == 0) cout << "-1\n";
            else {
                cout << arr.front() << "\n";
                arr.pop();
            }
        }
        else if (str == "size") {
            cout << arr.size() << "\n";
        }
        else if (str == "empty") {
            if (arr.empty()) cout << "1\n";
            else cout << "0\n";
        }
        else if (str == "front") {
            if (arr.size() == 0) cout << "-1\n";
            else cout << arr.front() << "\n";
        }
        else {
            if (arr.size() == 0) cout << "-1\n";
            else cout << arr.back() << "\n";
        }
    }
}