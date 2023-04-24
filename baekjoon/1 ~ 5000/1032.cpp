#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    string str;
    cin >> n >> str;
    n--;

    int len = str.size();
    string answer = str;
    while (n--) {
        string tmp;
        cin >> tmp;
        for (int i = 0; i < len; ++i) {
            if (answer[i] == '?') continue;
            if (answer[i] != tmp[i]) answer[i] = '?';
        }
    }

    cout << answer;
}