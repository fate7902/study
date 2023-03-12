#include <iostream>
#include <algorithm>
using namespace std;

#define endl "\n"

short arr[9][9] = { 0 };
bool tmpX[9][10] = { false };
bool tmpY[9][10] = { false };
bool area[9][10] = { false };

bool check(int x, int y, int k) {
    if (tmpX[x][k] == false && tmpY[y][k] == false && area[y / 3 + 3 * (x / 3)][k] == false) return true;
    return false;
}

void dfs(int cnt) {
    if (cnt == 81) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        exit(0);
    }
    else {
        short x = cnt / 9;
        short y = cnt % 9;
        if (arr[x][y] == 0) {
            for (int k = 1; k <= 9; ++k) {
                if (check(x, y, k) == true) {
                    arr[x][y] = k;
                    tmpX[x][k] = true;
                    tmpY[y][k] = true;
                    area[y / 3 + 3 * (x / 3)][k] = true;
                    dfs(cnt + 1);
                    arr[x][y] = 0;
                    tmpX[x][k] = false;
                    tmpY[y][k] = false;
                    area[y / 3 + 3 * (x / 3)][k] = false;
                }
            }
        }
        else dfs(cnt + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < 9; ++i) {        
        for (int j = 0; j < 9; ++j) {
            cin >> arr[i][j];
            tmpX[i][arr[i][j]] = true;
            tmpY[j][arr[i][j]] = true;
            area[j / 3 + 3 * (i / 3)][arr[i][j]] = true;
        }
    }

    dfs(0);
}