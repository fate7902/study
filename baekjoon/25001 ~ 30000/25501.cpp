#include <iostream>
#include <cstring>
using namespace std;

int cnt = 0;

int recursion(const char* s, int l, int r) {
    cnt++;
    if (l >= r) return 1;
    else if (s[l] != s[r]) return 0;
    else return recursion(s, l + 1, r - 1);
}

int isPalindrome(const char* s) {
    return recursion(s, 0, strlen(s) - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int case_num;
    string str;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cnt = 0;        
        cin >> str;
        cout << isPalindrome(const_cast<const char*>(str.c_str())) << " ";
        cout << cnt << "\n";
    }
}