#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int case_num, num;
    cin >> case_num;
    int arr[10001] = { 0 };
    for (int i = 0; i < case_num; ++i) {
        cin >> num;
        arr[num]++;
    }    

    for (int i = 1; i <= 10000; ++i) {
        if(arr[i] != 0){
            for(int j = 0; j < arr[i]; ++j){
                cout << i << "\n";
            }
        }
    }
}