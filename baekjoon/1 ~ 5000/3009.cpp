#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, int> pointX, pointY;
    int x, y;
    for (int i = 0; i < 3; ++i) {
        cin >> x >> y;
        if (pointX.find(x) == pointX.end()) pointX.insert(pair<int, int>(x, 1));
        else pointX[x]++;
        if (pointY.find(y) == pointY.end()) pointY.insert(pair<int, int>(y, 1));
        else pointY[y]++;
    }

    for (const auto& p : pointX) {
        if (p.second == 1) cout << p.first << " ";
    }
    for (const auto& p : pointY) {
        if (p.second == 1) cout << p.first << " ";
    }
}