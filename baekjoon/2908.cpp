#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int a, b;
    a = stoi(str1);
    b = stoi(str2);
    if (a > b) cout << a;
    else cout << b;
}