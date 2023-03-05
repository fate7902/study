#include <iostream>
using namespace std;

int main() {
    short num[101] = { 0, };
    int n, t;
    cin >> n >> t;

    for (int i = 1; i <= n; ++i) {
        num[i] = i;
    }

    int s, e, m;
    for (int i = 1; i <= t; ++i) {
        cin >> s >> e >> m;
        int size = e - s + 1;
        int p = 0;
        short* tmp = new short[size]();
        for (int j = m; j <= e; ++j) {
            tmp[p++] = num[j];
        }
        for (int j = s; j < m; ++j) {
            tmp[p++] = num[j];
        }
        for (int j = 0; j < size; ++j) {
            num[s++] = tmp[j];
        }
        delete[] tmp;
    }   

    for (int i = 1; i <= n; ++i) {
        cout << num[i] << " ";
    }
}