#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {    
    int row = arr1.size();
    int colA = arr1[0].size();
    int colB = arr2[0].size();
    vector<vector<int>> answer(row, vector<int>(colB, 0));
    for(int i = 0; i < row; ++i){        
        for(int j = 0; j < colB; ++j){
            for(int k = 0; k < colA; ++k){
                answer[i][j] += (arr1[i][k] * arr2[k][j]);
            }
        }
    }
    return answer;
}