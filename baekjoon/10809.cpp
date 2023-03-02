#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    cin >> str;
    for (int i = 0; i < 26; i++) {
        char ch = i + 'a';
        if (str.find(ch) == string::npos) {
            cout << "-1 ";
        }
        else {
            cout << str.find(ch) << " ";
        }
    }
}