#include <iostream>
using namespace std;

int arr[100]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    int max = -99999999;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        if (i >= k - 1) {
            int tmp = 0;
            for (int j = i - k + 1; j <= i; ++j) tmp += arr[j];
            max = max > tmp ? max : tmp;
        }
    }
    cout << max;
}