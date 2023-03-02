#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    cout << fixed;
    cout.precision(14);
    int case_num;
    cin >> case_num;
    double* array = new double[case_num];
    for (int i = 0; i < case_num; i++) {
        cin >> array[i];
    }
    double max = *max_element(array, array + case_num);
    for (int i = 0; i < case_num; i++) {
        array[i] = (array[i] / max) * 100;
    }
    double sum = accumulate(array, array + case_num, 0.0);    
    cout << sum / case_num;
}