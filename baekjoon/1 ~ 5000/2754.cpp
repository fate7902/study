#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;
    float grade = 4.0 - (str[0] - 'A');
    cout << fixed;
    cout.precision(1);
    if (grade == -1) grade = 0.0;
    if (grade != 0) grade += str[1] == '+' ? 0.3 : (str[1] == '-' ? -0.3 : 0.0); ;
    cout << grade;
}