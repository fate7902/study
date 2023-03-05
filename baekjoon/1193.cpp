#include <iostream>
using namespace std;

int calculate(int a) {
    return (a + 1) * a / 2;
}

int main() {
    int num, answer = 2;
    cin >> num;
    while (true) {
        if (num != 1) {
            if (calculate(answer - 1) < num && calculate(answer) >= num) {
                if (answer % 2 == 0) {
                    int diff = calculate(answer) - num;
                    cout << (answer - diff) << "/" << (1 + diff);
                    break;
                }
                else {
                    int diff = calculate(answer) - num;
                    cout << (1 + diff) << "/" << (answer - diff);
                    break;
                }
            }
            else {
                answer++;
            }
        }
        else {
            cout << "1/1";
            break;
        }
    }
}