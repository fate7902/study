#include <iostream>
#include <vector>
using namespace std;

int main() {
    int case_num;
    cin >> case_num;

    vector<int> array;
    array.emplace_back(2);
    for (int i = 3; i <= 10000; i++) {
        bool flag = false;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                flag = true;
                break;
            }
        }
        if (flag == false) array.emplace_back(i);
    }

    for (int i = 0; i < case_num; i++) {
        int num;
        cin >> num;
        int a = 0, b = 0, diff = 10000;
        for (int i = 0; i < array.size(); i++) {
            for (int j = i; j < array.size(); j++) {
                if (array[i] + array[j] == num) {
                    if (array[j] - array[i] < diff) {
                        diff = array[j] - array[i];
                        a = array[i];
                        b = array[j];
                    }
                }
                else if (array[i] + array[j] > num) {
                    break;
                }
            }
        }
        cout << a << " " << b << "\n";
    }
}