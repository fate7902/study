#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int n;
        cin >> n;
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            int cx, cy, r;
            cin >> cx >> cy >> r;
            int dis1 = pow(cx - x1, 2) + pow(cy - y1, 2);
            int dis2 = pow(cx - x2, 2) + pow(cy - y2, 2);
            if (pow(r, 2) > dis1 && pow(r, 2) < dis2) cnt++;
            if (pow(r, 2) < dis1 && pow(r, 2) > dis2) cnt++;
        }
        cout << cnt << endl;
    }
}