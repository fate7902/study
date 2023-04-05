#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    int point[300];
    for (int i = 0; i < n; ++i) cin >> point[i];

    int arr[300][2];
    arr[0][0] = arr[0][1] = point[0];
    for (int i = 1; i < n; ++i) {
        if (i == 1) {
            arr[i][0] = point[i - 1] + point[i];
            arr[i][1] = point[i];
        }
        else {
            arr[i][0] = point[i] + arr[i - 1][1];
            arr[i][1] = point[i] + max(arr[i - 2][0], arr[i - 2][1]);
        }
    }

    cout << max(arr[n - 1][0], arr[n - 1][1]);
}