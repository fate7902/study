#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        int dis1 = pow(x2 - x1, 2) + pow(y2 - y1, 2);
        int dis2 = pow(r1 + r2, 2);
        int dis3 = pow(r1 - r2, 2);
        if (x1 == x2 && y1 == y2 && r1 == r2) cout << "-1" << endl;
        else if (dis1 > dis2 || dis1 < dis3) cout << "0" << endl;
        else if (dis1 == dis2 || dis1 == dis3) cout << "1" << endl;
        else if (dis1 > dis3 && dis1 < dis2) cout << "2" << endl;
    }
}