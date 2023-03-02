#include <iostream>
using namespace std;

int main() {
    int num, sum = 0;
    char ch;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> ch;
        sum += (int)(ch - '0');
    }
    cout << sum;
}