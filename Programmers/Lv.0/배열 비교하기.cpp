#include <string>
#include <vector>
#include <numeric>

using namespace std;

int solution(vector<int> arr1, vector<int> arr2) {  
    if(arr1.size() != arr2.size()){
        return arr1.size() > arr2.size() ? 1 : -1;
    }
    else{
        int a = accumulate(arr1.begin(), arr1.end(), 0);
        int b = accumulate(arr2.begin(), arr2.end(), 0);
        return a == b ? 0 : (a > b ? 1 : -1);
    }
}