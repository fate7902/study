#include <iostream>
#include <string>
#include <deque>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    deque<int> arr;
    while (n--) {
        string str;
        cin >> str;
        if (str == "push_front") {
            int tmp;
            cin >> tmp;
            arr.emplace_front(tmp);
        }
        else if (str == "push_back") {
            int tmp;
            cin >> tmp;
            arr.emplace_back(tmp);
        }
        else if (str == "pop_front") {
            if (arr.empty()) cout << "-1\n";
            else {
                cout << arr.front() << "\n";
                arr.pop_front();
            }
        }
        else if (str == "pop_back") {
            if (arr.empty()) cout << "-1\n";
            else {
                cout << arr.back() << "\n";
                arr.pop_back();
            }
        }
        else if (str == "size") cout << arr.size() << "\n";
        else if (str == "empty") {
            if(arr.empty()) cout << "1\n";
            else cout << "0\n";
        }
        else if (str == "front") {
            if (arr.empty()) cout << "-1\n";
            else cout << arr.front() << "\n";
        }
        else {
            if (arr.empty()) cout << "-1\n";
            else cout << arr.back() << "\n";
        }
    }
}