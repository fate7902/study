#include <iostream>
#include <cmath>
using namespace std;

void hanoi(int n, int start, int destination, int pass) {
    if (n == 1) cout << start << " " << destination << "\n";
    else {
        hanoi(n - 1, start, pass, destination);
        cout << start << " " << destination << "\n";
        hanoi(n - 1, pass, destination, start);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int num;
    cin >> num;
    cout << (int)pow(2, num) - 1 << "\n";
    hanoi(num, 1, 3, 2);
}