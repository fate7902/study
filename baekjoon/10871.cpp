#include <iostream>
using namespace std;

int main() {
    int case_num, comp_value;    
    cin >> case_num >> comp_value;
    int* num = new int [case_num];
    for(int i = 0; i < case_num; ++i){
        cin >> num[i];
    }
    for(int i = 0; i < case_num; ++i){
        if(num[i] < comp_value){
            cout << num[i] << " ";
        }
    }
    delete[] num;
}