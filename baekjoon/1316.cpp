#include <iostream>
#include <algorithm>
using namespace std;

bool IsGroupWord(string& str) {
    short cnt[26] = { 0, };
    string new_word;
    for (int i = 0; i < str.size(); i++) {
        if (i + 1 != str.size()) {
            if (str[i] != str[i + 1]) {
                new_word += str[i];
            }
        }
        else {
            new_word += str[i];
        }
    }
    for (int i = 0; i < new_word.size(); i++) {
        cnt[new_word[i] - 'a']++;
    }
    if (*max_element(cnt, cnt + 26) > 1) return false;
    else return true;
}

int main() {
    string str;
    int case_num, cnt = 0;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> str;
        if (true == IsGroupWord(str)) {
            cnt++;
        }
    }
    cout << cnt;
}