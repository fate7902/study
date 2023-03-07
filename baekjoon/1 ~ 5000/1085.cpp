#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int x, y, w, h;
    cin >> x >> y >> w >> h;
    
    int dis = 0;
    dis = x;
    dis = min(dis, w - x);
    dis = min(dis, y);
    dis = min(dis, h - y);
    cout << dis;
}