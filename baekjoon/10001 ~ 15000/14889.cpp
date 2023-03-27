#include<iostream>
using namespace std;

void dfs(const short*& arr, bool*& sel, int cnt, int person, int n, int& min_value) {
    if (cnt == n / 2) {
        int start = 0, link = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (sel[i] && sel[j]) start += arr[(i - 1) * n + j - 1];
                if (!sel[i] && !sel[j]) link += arr[(i - 1) * n + j - 1];
            }
        }
        int temp = start - link >= 0 ? start - link : link - start;
        min_value = min_value > temp ? temp : min_value;
        return;
    }
    else {
        for (int i = person; i < n; ++i) {
            sel[i] = true;
            dfs(arr, sel, cnt + 1, i + 1, n, min_value);
            sel[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    short* arr = new short[20 * 20];
    for (int i = 0; i < n * n; ++i) {
        cin >> arr[i];
    }

    bool* sel = new bool[21]();
    int min_value = 2100000000;
    dfs((const short*&)arr, sel, 0, 1, n, min_value);
    cout << min_value;

    delete[] arr;
    delete[] sel;
}