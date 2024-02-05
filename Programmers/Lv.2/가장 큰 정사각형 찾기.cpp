#include <iostream>
#include <vector>
using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    int row = board.size(), col = board[0].size();
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            if(i == 0 || j == 0) answer = max(answer, board[i][j]);
            else if(board[i][j] == 1){
                board[i][j] = min(min(board[i][j - 1], board[i - 1][j]), board[i - 1][j - 1]) + 1;
                answer = max(answer, board[i][j]);
            }
        }
    }
    return answer * answer;
}