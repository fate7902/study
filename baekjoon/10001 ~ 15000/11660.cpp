#include <iostream>
using namespace std;

int arr[1025][1025]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;    
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int tmp;
            cin >> tmp;
            arr[i][j] = arr[i][j - 1] + tmp;
        }        
    }

    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int result = 0;
        for (int j = 0; j <= x2 - x1; ++j) {
            result += (arr[x2 - j][y2] - arr[x2 - j][y1 - 1]);
        }
        cout << result << "\n";
    }
}