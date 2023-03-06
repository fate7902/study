#include <iostream>
using namespace std;

int main() {
    int h,m,t;
    cin >> h >> m >> t;
    if(m + t >= 60)
    {
        int st = (m + t) / 60;
        if(h + st > 23)
        {
            cout << h + st - 24 << " " << (m + t) % 60;
        }
        else
        {
            cout << h + st << " " << (m + t) % 60;
        }
    }
    else
    {
        cout << h << " " << m + t;
    }
}