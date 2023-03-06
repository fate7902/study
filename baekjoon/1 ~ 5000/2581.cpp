#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> array;
    for (int i = m; i <= n; i++) {
        if (i > 1) {
            int cnt = 0;
            for (int j = 1; j <= i; j++) {
                if (i % j == 0) {
                    if (cnt < 2) cnt++;
                    else {
                        cnt++;
                        break;
                    }
                }
            }
            if (cnt == 2) array.emplace_back(i);
        }
    }
    if (array.size() != 0) {
        cout << accumulate(array.begin(), array.end(), 0) << endl
            << *min_element(array.begin(), array.end());
    }
    else cout << "-1";
}