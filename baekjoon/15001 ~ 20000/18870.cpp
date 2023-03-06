#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int case_num, num;
    cin >> case_num;
    int* arr1 = new int[case_num];
    vector<int> tmp(case_num);
    for (int i = 0; i < case_num; i++) {
        cin >> num;
        arr1[i] = num;
        tmp[i] = num;
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

    for (int i = 0; i < case_num; i++) {
        cout << lower_bound(tmp.begin(), tmp.end(), arr1[i]) - tmp.begin() << " ";
    }

    delete[] arr1;
}