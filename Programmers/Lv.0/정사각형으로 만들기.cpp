#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr) {
    int len = arr.size() > arr[0].size() ? arr.size() : arr[0].size();
    vector<vector<int>> answer(len, vector<int>(len, 0));
    for(int i = 0; i < arr.size(); ++i){
        for(int j = 0; j < arr[0].size(); ++j){
            answer[i][j] = arr[i][j];
        }
    }
    return answer;
}