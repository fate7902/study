#include <iostream>
using namespace std;

int main() {
    string str;
    int num, sum = 0;
    cin >> str;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'S' || str[i] == 'V' || str[i] == 'Y' || str[i] == 'Z') {
            num = (int)(str[i] - 'A') / 3 + 2;
        }
        else {
            num = (int)(str[i] - 'A') / 3 + 3;
        }
        sum += num;
    }
    cout << sum;
}