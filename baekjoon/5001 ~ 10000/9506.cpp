#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    int n;

    while (cin >> n) {
        if (n == -1) break;
        vector<int> list;
        for (int i = 1; i < n; ++i) {
            if (n % i == 0) list.emplace_back(i);
        }
        if (n == accumulate(list.begin(), list.end(), 0)) {
            cout << n << " = ";
            for (int j = 0; j < list.size() - 1; ++j) {
                cout << list[j] << " + ";
            }
            cout << list[list.size() - 1] << endl;
        }
        else cout << n << " is NOT perfect." << endl;
    }
}