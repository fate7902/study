#include <iostream>
using namespace std;

long long int func(long long int& a, long long int b, long long int& c) {
    if (b == 1) return a % c;
    long long int tmp = func(a, b / 2, c);
    tmp = tmp * tmp % c;
    if (b % 2 == 0) return tmp;
    else return tmp * a % c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long int a, b, c;
    cin >> a >> b >> c;
    cout << func(a, b, c);
}