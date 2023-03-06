#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int case_num;
    cin >> case_num;
    int* array = new int[case_num];
    for(int i = 0; i < case_num; i++){
        cin >> array[i];
    }    
    cout << *min_element(array, array + case_num) << " " << *max_element(array, array + case_num);
}