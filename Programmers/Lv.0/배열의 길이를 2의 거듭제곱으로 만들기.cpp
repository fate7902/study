#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr) {
    int p = 0;
    while ((1 << p) < arr.size()) p++;
    arr.insert(arr.end(), (1 << p) - arr.size(), 0);
    return arr;
}