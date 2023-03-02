#include <iostream>
using namespace std;

int main() {
    short num[100] = { 0, };
    int n, m;
    int i, j, k;
    cin >> n >> m;
    
    for(int a = 0; a < m; ++a){
        cin >> i >> j >> k;
        for(int b = i; b <=j; ++b){
            num[b - 1] = k;
        }
    }
    
    for(int a = 0; a < n; ++a){
        cout << num[a] << " ";
    }
}