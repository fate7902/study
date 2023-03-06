#include <iostream>
using namespace std;

void star(int x, int y, int len) {
    if (x / len % 3 == 1 && y / len % 3 == 1) cout << " ";
    else if (len / 3 == 0) cout << "*";
    else star(x, y, len / 3);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int len;
    cin >> len;
    for (int x = 0; x < len; x++) {
        for (int y = 0; y < len; y++) {
            star(x, y, len);
        }
        cout << "\n";
    }
}