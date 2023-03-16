#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    while (true) {
        cin >> n;
        int answer = 0;
        if (n != 0) {
            bool* flag = new bool[2 * n + 1];
            for (int i = 0; i <= 2 * n; i++) {
                flag[i] = true;
            }
            flag[0] = flag[1] = false;
            for (int i = 2; i <= sqrt(2 * n); i++) {
                if (flag[i] == false) continue;
                for (int j = i * i; j <= 2 * n; j += i) {
                    flag[j] = false;
                }
            }

            for (int i = n + 1; i <= 2 * n; i++) {
                if (flag[i] == true) answer++;
            }
            cout << answer << '\n';
            delete[] flag;
        }
        else break;
        
    }
}