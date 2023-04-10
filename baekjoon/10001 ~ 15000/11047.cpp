#include <iostream>
using namespace std;

int value[11]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;    
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) cin >> value[i];

    int cnt = 0;
    while (k > 0) {
        if (k / value[n] > 0) {
            cnt += (k / value[n]);
            k %= value[n];
        }
        n--;
    }

    cout << cnt;
}