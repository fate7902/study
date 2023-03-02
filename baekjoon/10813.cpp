#include <iostream>
using namespace std;

int main() {
    short num[101] = { 0, };
    int n, m;
    int i, j;
    cin >> n >> m;
    
    for(int a = 1; a <= n; ++a){
        num[a] = a;
    }
    
    for(int a = 1; a <= m; ++a){
        cin >> i >> j;
        short tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
    }
    
    for(int a = 1; a <= n; ++a){
        cout << num[a] << " ";
    }
}