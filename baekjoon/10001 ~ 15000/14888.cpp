#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int cal(const vector<int>& arr, const vector<short>& symbol) {
    int sum = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        switch (symbol[i - 1]) {
        case 0:
            sum += arr[i];
            break;
        case 1:
            sum -= arr[i];
            break;
        case 2:
            sum *= arr[i];
            break;
        case 3:
            sum /= arr[i];
            break;
       }
    }
    return sum;
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    vector<short> symbol;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];        
    }
    for (int i = 0; i < 4; i++) {
        int tmp;
        cin >> tmp;
        symbol.insert(symbol.end(), tmp, i);
    }

    int max_value = -1000000001;
    int min_value = 1000000001;    
    do {
        int result = cal(arr, symbol);
        max_value = max(max_value, result);
        min_value = min(min_value, result);        
    } while (next_permutation(symbol.begin(), symbol.end()));

    cout << max_value << "\n" << min_value;
}