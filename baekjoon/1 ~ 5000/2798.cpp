#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, tmp, sum = 0, max = 0;
    cin >> n >> m;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        arr[i] = tmp;
    }

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                sum = arr[i] + arr[j] + arr[k];
                if (sum > max && sum <= m) max = sum;
            }
        }
    }

    cout << max;
}