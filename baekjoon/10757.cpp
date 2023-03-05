#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string a, b;
string answer;

int main() {
    int freeNum = 0;
    cin >> a >> b;
    int as = a.size();
    int bs = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    if (as >= bs) {
        for (int i = 0; i < as; i++) {
            int sum;
            if (bs <= i) {
                sum = (int)(a[i] - '0') + freeNum;
            }
            else {
                sum = (int)(a[i] + b[i] - '0' * 2) + freeNum;
            }
            answer += (char)(sum % 10 + '0');
            if (sum >= 10) freeNum = 1;
            else freeNum = 0;
        }
    }
    else {
        for (int i = 0; i < bs; i++) {
            int sum;
            if (as <= i) {
                sum = (int)(b[i] - '0') + freeNum;
            }
            else {
                sum = (int)(a[i] + b[i] - '0' * 2) + freeNum;
            }
            answer += (char)(sum % 10 + '0');
            if (sum >= 10) freeNum = 1;
            else freeNum = 0;
        }
    }
    if (freeNum > 0) answer += (char)(freeNum + '0');
    reverse(answer.begin(), answer.end());
    cout << answer;
}