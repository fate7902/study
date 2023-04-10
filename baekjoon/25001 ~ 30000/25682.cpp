#include <iostream>
#include <algorithm>
using namespace std;

int B[2001][2001]{};
int W[2001][2001]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;    
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;
            B[i][j] = B[i][j - 1] + B[i - 1][j] - B[i - 1][j - 1];
            W[i][j] = W[i][j - 1] + W[i - 1][j] - W[i - 1][j - 1];
            if ((i + j) % 2 == 0) {               
                if (c == 'W') B[i][j]++;                
                else W[i][j]++;
            }
            else {                
                if (c == 'B') B[i][j]++;
                else W[i][j]++;
            }
        }
    }

    int cnt = k * k;
    for (int i = k; i <= n; ++i) {
        for (int j = k; j <= m; ++j) {
            int tmpW = W[i][j] - W[i - k][j] - W[i][j - k] + W[i - k][j - k];
            int tmpB = B[i][j] - B[i - k][j] - B[i][j - k] + B[i - k][j - k];
            cnt = min(min(tmpW, tmpB), cnt);
        }
    }

    cout << cnt;
}