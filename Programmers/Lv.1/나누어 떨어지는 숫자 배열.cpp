#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr, int divisor) {
    vector<int> answer;
    for(const auto& a : arr){
        if(a % divisor == 0) answer.emplace_back(a);
    }
    sort(answer.begin(), answer.end());
    if(answer.size() == 0) answer.emplace_back(-1);
    return answer;
}