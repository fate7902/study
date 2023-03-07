#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int series = 1;
    int movieName = 666;
    int temp;
    while (series != n) {
        movieName++;
        temp = movieName;
        while (temp >= 666) {
            if (temp % 1000 == 666) {
                series++;
                break;
            }
            else temp /= 10;
        }
    }
    cout << movieName;
}