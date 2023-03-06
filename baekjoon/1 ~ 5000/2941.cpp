#include <iostream>
using namespace std;

int main() {
    string array[8] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };
    string str;
    cin >> str;
    int start = 0, num = 0;
    bool flag = true;
    do {
        bool find = false;
        for (int i = 0; i < 8; i++) {
            if (array[i].compare(str.substr(start, 2)) == 0) {
                num++;
                start += 2;
                find = true;
                break;
            }
        }
        if (find == false) {
            for (int i = 0; i < 8; i++) {
                if (array[i].compare(str.substr(start, 3)) == 0) {
                    num++;
                    start += 3;
                    find = true;
                    break;
                }
            }
            if (find == false) {
                start += 1;
                num++;
            }
        }
        if (start == str.size()) {
            flag = false;
        }
    } while (flag);
    cout << num;
}