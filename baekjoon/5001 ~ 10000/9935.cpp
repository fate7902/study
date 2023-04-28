#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str, eraser;
    cin >> str >> eraser;
    string tmp{};
    int len = str.size();
    for (int i = 0; i < len; ++i) {        
        tmp += str[i];

        int eraser_len = eraser.size();
        int tmp_len = tmp.size();
        if (tmp_len >= eraser_len) {
            bool flag = false;
            if (tmp.back() == eraser.back()) {
                for (int j = 0; j < eraser_len; ++j) {
                    if (tmp[tmp_len - eraser_len + j] != eraser[j]) {
                        flag = true;
                        break;
                    }
                }
                if (flag == false) {
                    for (int k = 0; k < eraser_len; ++k) {
                        tmp.pop_back();
                    }
                }
            }
        }
    }

    if (tmp.size() == 0) cout << "FRULA";
    else cout << tmp;
}