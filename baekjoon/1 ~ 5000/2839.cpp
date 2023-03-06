#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int case_num = n / 3, num;
    bool check = false;
    for (int i = 0; i < case_num; i++) {
        if ((n - (3 * i)) % 5 == 0) {
            check = true;
            num = (n - (3 * i)) / 5 + i;
            break;
        }
    }
    if (check == true) cout << num;
    else {
        if (n % 3 != 0) cout << "-1";
        else cout << n / 3;
    }
}