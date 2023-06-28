#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    for(long long int i = left; i <= right; ++i){
        int row = i / n + 1;
        int origin_val = i - (row - 1) * n + 1;
        int val = origin_val >= row ? origin_val : row;
        answer.emplace_back(val);        
    }
    return answer;
}