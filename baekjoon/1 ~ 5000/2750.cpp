#include <iostream>
#include <set>
using namespace std;

int main() {
    int case_num, num;
    cin >> case_num;
    
    set<int> array;
    for (int i = 0; i < case_num; i++) {
        cin >> num;
        array.insert(num);
    }
    
    for (const auto& n : array) {
        cout << n << "\n";
    }
}