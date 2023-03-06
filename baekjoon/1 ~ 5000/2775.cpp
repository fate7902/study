#include <iostream>
using namespace std;

int calculate(int k, int n) {
    if (k == 0) return n;
    else if (n == 1) return n;
    else return calculate(k, n - 1) + calculate(k - 1, n);
}

int main() {
    int case_num;
    cin >> case_num;
    int k, n;
    for (int i = 0; i < case_num; i++) {
        cin >> k >> n;
        if (k == 0) cout << n << endl;
        else if (n == 1) {
            cout << n << endl;
        }else {            
            cout << calculate(k, n) << endl;
        }
    }
}