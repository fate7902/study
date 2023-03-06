#include <iostream>
using namespace std;

int main() {
    int num;
    bool check[100][100] = { false, };
    int answer = 0;
    cin >> num;
    int x, y;

    for (int i = 0; i < num; i++) {
        cin >> x >> y;
        for (int j = x; j < x + 10; j++) {
            for (int k = y; k < y + 10; k++) {
                if (false == check[j][k]) {
                    check[j][k] = true;
                    answer++;
                }
            }
        }
    }
    cout << answer;
}