#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;
    
    int cnt[26]{};
    int len = str.size();
    for (int i = 0; i < len; ++i) {
        cnt[str[i] - 'a']++;
    }

    for (const auto& a : cnt) {
        cout << a << " ";
    }
}