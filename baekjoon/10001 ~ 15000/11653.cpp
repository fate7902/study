#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> array;
    for(int i = 2; i <= n; i++){
        if(n % i == 0) {
            array.emplace_back(i);
            n /= i;
            i = 1;
        }
    }
    
    for(int i = 0; i < array.size(); i++){
        cout << array[i] << endl;
    }
}