#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    cin >> str;
    string tmp(str.rbegin(), str.rend());

    if (str.compare(tmp) == 0) cout << "1";
    else cout << "0";
}