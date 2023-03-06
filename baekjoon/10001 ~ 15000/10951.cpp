#include <iostream>
using namespace std;

int main() {
    int a, b;
    while(!(cin >> a >> b).eof()){        
        cout << a + b << endl;
    }
}

// 문제에서 입력 갯수가 주어지지 않았으므로 eof를 확인하는 과정이 필요하다.