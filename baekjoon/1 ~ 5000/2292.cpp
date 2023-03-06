#include <iostream>
using namespace std;

int calculate(int a) {
    return 3 * a * (a - 1) + 1;
}

int main() {
    int num, answer = 2;
    cin >> num;
    while (true) {
        if (num == 1) {
            cout << num;
            break;
        }
        else {
            if (calculate(answer - 1) < num && calculate(answer) >= num) {
                cout << answer;
                break;
            }
            answer++;
        }
    }
}