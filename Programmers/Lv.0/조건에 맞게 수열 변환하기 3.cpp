#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr, int k) {
    vector<int> answer(arr.size());
    if (k % 2 == 0) transform(arr.begin(), arr.end(), answer.begin(), [k](int a) { return a + k; });
    else transform(arr.begin(), arr.end(), answer.begin(), [k](int a) { return a * k; });
    return answer;
}