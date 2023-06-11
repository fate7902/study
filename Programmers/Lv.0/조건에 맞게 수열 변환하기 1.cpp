#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr) {
    for_each(arr.begin(), arr.end(), [](auto& a){
        if(a >= 50 && a % 2 == 0) a /= 2;
        else if(a < 50 && a % 2 == 1) a *= 2;
    });
    return arr;
}