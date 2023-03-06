#include <iostream>
using namespace std;

int main(){
    int num[3];
    for(int i=0; i<3; i++)
        cin >> num[i];
    cout << (num[0]+num[1])%num[2] << endl;
    cout << ((num[0]%num[2]) + (num[1]%num[2]))%num[2] << endl;
    cout << (num[0]*num[1])%num[2] << endl;
    cout << ((num[0]%num[2]) * (num[1]%num[2]))%num[2] << endl;
}