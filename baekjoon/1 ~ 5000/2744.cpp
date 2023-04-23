#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    int len = str.size();
    for (int i = 0; i < len; ++i) {
        if (islower(str[i]) != 0) str[i] = toupper(str[i]);
        else str[i] = tolower(str[i]);
    }
    cout << str;
}