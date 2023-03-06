#include <iostream>
using namespace std;

int main() {
    int num;
    cin >> num;

    int max_line;
    max_line = num * 2 - 1;

    for (int i = 1; i <= max_line; ++i) {
        if (i <= num) {
            for (int j = 1; j <= max_line; ++j) {
                if (j > num - i && j < num + i) cout << "*";
                else if(j <= num - i)cout << " ";
            }
        }
        else {
            for (int j = 1; j <= max_line; ++j) {
                if (j <= i - num) cout << " ";
                else if(j <= max_line - (i - num)) cout << "*";
            }
        }
        cout << endl;
    }
}