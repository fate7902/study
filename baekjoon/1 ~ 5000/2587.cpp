#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    int num;
    vector<int> array;
    for (int i = 0; i < 5; i++) {
        cin >> num;
        array.emplace_back(num);
    }
    sort(array.begin(), array.end());
    cout << accumulate(array.begin(), array.end(), 0) / array.size() << "\n";
    cout << array[array.size() / 2];
}