#include <iostream>
using namespace std;

int main() {
    int case_num, a, b;
    cin.tie(NULL);    
    ios::sync_with_stdio(false);
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> a >> b;
        cout << a + b << "\n";
    }
}

// cin.tie(NULL), ios::sync_with_stdio(false), endl 대신 \n이 
// 입출력 속도를 향상시킴 단 순서는 보장안됨