#include <iostream>
using namespace std;

int main() {
    int case_num, num;
    string str;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> num >> str;
        for (int j = 0; j < str.size(); j++) {
            for (int k = 0; k < num; k++) {
                cout << str[j];
            }
        }
        cout << endl;
    }
}