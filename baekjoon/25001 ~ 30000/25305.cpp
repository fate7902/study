#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, k, score;
    cin >> n >> k;
    vector<int> array;
    for (int i = 0; i < n; i++) {
        cin >> score;
        array.emplace_back(score);
    }
    sort(array.rbegin(), array.rend());
    cout << array[k - 1];
}