#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    string str;
    cin >> str;    
    int flag[26] = { 0, };
    int index = 0;
    for (int i = 0; i < str.size(); i++) {
        str[i] = tolower(str[i]);
        flag[str[i] - 'a']++;
    }
    int max = *max_element(flag, flag + 26);
    int max_index = max_element(flag, flag + 26) - flag;
    for (int i = 0; i < 26; i++) {
        if (max == flag[i]) index++;
    }
    if (1 == index) cout << (char)(max_index + 'A');
    else cout << "?";
}