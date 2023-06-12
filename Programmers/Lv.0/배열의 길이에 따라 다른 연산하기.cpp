#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, int n) {
    int idx = arr.size() % 2 == 0 ? 1 : 0;
    while(idx < arr.size()){
            arr[idx] += n;
            idx += 2;
    }
    return arr;
}