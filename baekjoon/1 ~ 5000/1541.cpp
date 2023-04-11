#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    vector<int> num;
    vector<char> sign;
    int len = str.size();
    int pos = 0;
    for (int i = 0; i < len; ++i) {
        if (isdigit(str[i]) == 0) {
            sign.emplace_back(str[i]);
            num.emplace_back(stoi(str.substr(pos, i - pos)));
            pos = i + 1;
        }
    }
    num.emplace_back(stoi(str.substr(pos, len - pos)));

    int answer = num[0];
    len = sign.size();
    bool flag = false;
    for (int i = 0; i < len; ++i) {
        if (sign[i] == '-') {
            flag = true;
            answer -= num[i + 1];
        }
        else {
            if (flag == true) answer -= num[i + 1];
            else answer += num[i + 1];
        }
    }

    cout << answer;
}