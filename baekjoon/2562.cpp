#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int array[9];
    for(int i = 0; i < 9; ++i){
        cin >> array[i];
    }
    cout << *max_element(array, array + 9) << endl;
    cout << max_element(array, array + 9) - array + 1 << endl;
}