#include <iostream>
using namespace std;

int main() {
    int line;
    cin >> line;
    for(int i = 1; i <= line; i++){
        for(int j = line; j >0; j--){
            if(i >= j) cout << "*";
            else cout << " ";
        }
        cout << endl;
    }
}