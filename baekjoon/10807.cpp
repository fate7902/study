#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int case_num, find_num;
    cin >> case_num;
    int* array = new int[case_num];
    for (int i = 0; i < case_num; ++i) {
        cin >> array[i];
    }
    cin >> find_num;
    cout << count(array, array + case_num, find_num);
    delete[] array;
}