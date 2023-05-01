#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 5;
    int sum = 0;
    while (n--) {
        int tmp;
        cin >> tmp;
        if (tmp < 40) tmp = 40;
        sum += tmp;
    }
    cout << sum / 5;
}