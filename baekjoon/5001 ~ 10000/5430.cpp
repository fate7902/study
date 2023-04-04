#include <iostream>
#include <string>
#include <cctype>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, pos = 1;
        string func, str;
        cin >> func >> n >> str;

        deque<int> arr;
        for (int i = 1; i < str.size(); ++i) {
            if (str[i] == ',' || str[i] == ']' && i != 1) {
                arr.emplace_back(stoi(str.substr(pos, i - pos)));
                pos = i + 1;
            }
        }

        int cnt = count(func.begin(), func.end(), 'D');
        if (arr.size() < cnt) {
            cout << "error\n";
            continue;
        }

        cnt = 1;
        for (int i = 0; i < func.size(); ++i) {
            if (func[i] == 'R') cnt *= -1;
            else {
                if (cnt == -1) arr.pop_back();
                else arr.pop_front();                
            }
        }

        if(arr.empty()) cout << "[]\n";
        else {
            cout << "[";
            if (cnt == 1) {
                for (int i = 0; i < arr.size() - 1; ++i) {
                    cout << arr[i] << ",";
                }
                cout << arr.back() << "]\n";
            }
            else {
                for (int i = arr.size() - 1; i > 0; --i) {
                    cout << arr[i] << ",";
                }
                cout << arr.front() << "]\n";
            }
        }
    }
}