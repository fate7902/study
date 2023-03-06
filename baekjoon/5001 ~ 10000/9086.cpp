#include <iostream>
#include <string>
using namespace std;

int main() {
    int case_num;
    string str;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> str;        
        cout << str[0] << str[str.size() - 1] << endl;
    }
}