#include <iostream>
using namespace std;

int a[101][101]{};
int b[101][101]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n1, m1, n2, m2;

    cin >> n1 >> m1;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            cin >> a[i][j];
        }
    }

    cin >> m2 >> n2;
    for (int i = 0; i < m2; ++i) {
        for (int j = 0; j < n2; ++j) {
            cin >> b[i][j];
        }
    }

    for (int i = 0; i < n1; ++i) {        
        for (int x = 0; x < n2; ++x) {
            int cnt = 0;
            for (int j = 0; j < m1; ++j) {
                cnt += (a[i][j] * b[j][x]);
            }
            cout << cnt << " ";
        }
        cout << "\n";
    }
}