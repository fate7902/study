#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int case_num, num;
    cin >> case_num;
    vector<int> array(case_num);
    for(int i = 0; i < case_num; i++){
        cin >> array[i];        
    }
    sort(array.begin(), array.end());
    for(const auto& a : array){
        cout << a << "\n";
    }
}