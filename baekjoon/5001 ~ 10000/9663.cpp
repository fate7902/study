#include <iostream>
using namespace std;

int dfs(int row, int n, int* col, bool* check_row, bool* check_d1, bool* check_d2) {
    if (row == n) {
        return 1;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!check_row[i] && !check_d1[row - i + n - 1] && !check_d2[row + i]) {
            col[row] = i;
            check_row[i] = true;
            check_d1[row - i + n - 1] = true;
            check_d2[row + i] = true;
            cnt += dfs(row + 1, n, col, check_row, check_d1, check_d2);
            check_row[i] = false;
            check_d1[row - i + n - 1] = false;
            check_d2[row + i] = false;
        }
    }

    return cnt;
}

int main() {
    int n;
    cin >> n;

    int* col = new int[n];
    bool* check_row = new bool[n]();
    bool* check_d1 = new bool[2 * n - 1]();
    bool* check_d2 = new bool[2 * n - 1]();

    int answer = dfs(0, n, col, check_row, check_d1, check_d2);
    cout << answer;

    delete[] col;
    delete[] check_row;
    delete[] check_d1;
    delete[] check_d2;
}