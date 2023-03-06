#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int array[81];
    for (int i = 0; i < 81; i++) {
        cin >> array[i];
    }
    int max_index = max_element(array, array + 81) - array;
    int max = *max_element(array, array + 81);
    cout << max << endl;
    cout << max_index / 9 + 1 << " " << max_index % 9 + 1;
}