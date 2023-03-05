#include <iostream>
using namespace std;

int main() {
    int case_num;    
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        int h, w, n;
        cin >> h >> w >> n;        
        if(n % h != 0){
            cout << n % h;
            if (n / h + 1 < 10) {
                cout << "0" << n / h + 1;
            }
            else {
                cout << n / h + 1;
            }
        }
        else{
            cout << h;
            if (n / h < 10) {
                cout << "0" << n / h;
            }
            else {
                cout << n / h;
            }
        }

        cout << endl;
    }
}