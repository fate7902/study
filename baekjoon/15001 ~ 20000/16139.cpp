#include <iostream>
#include <string>
using namespace std;

int sum[200001][26]{};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    int q;
    cin >> str >> q;

    int len = str.size();
    for (int i = 1; i <= len; ++i) {
        for (int j = 0; j < 26; ++j) {
            sum[i][j] = sum[i - 1][j];
        }
        sum[i][str[i - 1] - 'a']++;
    }

    while (q--) {
        char c;
        int start, end;
        cin >> c >> start >> end;

        cout << sum[end + 1][c - 'a'] - sum[start][c - 'a'] << "\n";
    }
}