#include <iostream>
using namespace std;

int main() {
    int num;
    bool array[30] = {false, };
    for(int i = 0 ; i < 30; ++i){
        cin >> num;
        array[num - 1] = true;
    }
    for(int i = 0 ; i < 30; ++i){
        if(false == array[i]){
            cout << i + 1 << endl;
        }
    }
}