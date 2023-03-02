#include <iostream>
using namespace std;

int main() {
    int num, cnt = 0;
    int array[42] = {0, };
    for(int i = 0; i < 10; i++){
        cin >> num;
        array[num % 42]++;
    }
    for(int i = 0; i < 42; i++){
        if(array[i] != 0) cnt++;
    }
    cout << cnt;
}