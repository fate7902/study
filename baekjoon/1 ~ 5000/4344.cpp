#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    int case_num, num;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> num;
        int* array = new int[num];
        for (int i = 0; i < num; i++) {
            cin >> array[i];
        }
        double average = accumulate(array, array + num, 0.0) / num;
        int cnt = 0;
        for (int i = 0; i < num; i++) {
            if (array[i] > average) cnt++;
        }
        cout << fixed;
        cout.precision(3);
        cout << ((double)cnt / (double)num) * 100.f << "%" << endl;
        delete[] array;
    }
}