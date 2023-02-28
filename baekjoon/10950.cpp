#include <iostream>

using namespace std;

int main() {
    int case_num;
    cin >> case_num;
    int* input = new int[case_num * 2];
    for (int i = 0; i < case_num * 2; i += 2) {
        cin >> input[i] >> input[i + 1];
    }
    for (int i = 0; i < case_num * 2; i += 2) {
        cout << input[i] + input[i + 1] << endl;
    }
    delete[] input;
}

// 동적 할당 후 반드시 delete 잊지 않기