#include <iostream>
using namespace std;

int findNum(int n) {
    int answer, temp;
    for (int i = 1; i < n; i++) {
        answer = i;
        temp = i;
        while (temp > 0) {
            answer += temp % 10;
            temp /= 10;
        }
        if (answer == n) return i;
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    cout << findNum(n);
}