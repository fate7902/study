#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, vector<vector<int>> intervals) {
    vector<int> answer;
    for(int i = 0; i < intervals.size(); ++i){
        vector<int> tmp(arr.begin() + intervals[i][0], arr.begin() + intervals[i][1] + 1);
        answer.insert(answer.end(), tmp.begin(), tmp.end());
    }
    return answer;
}