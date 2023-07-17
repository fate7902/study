#include <string>
#include <vector>

using namespace std;

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    vector<string> new_board(board);    
    while(true){
        bool check = false;
        for(int i = 0; i < m - 1; ++i){
            for(int j = 0; j < n - 1; ++j){
                if(board[i][j] == ' ') continue;
                if(board[i][j] == board[i][j + 1] &&
                   board[i][j] == board[i + 1][j] &&
                   board[i][j] == board[i + 1][j + 1]){
                    if(new_board[i][j] != ' ') {answer++; new_board[i][j] = ' ';}
                    if(new_board[i][j + 1] != ' ') {answer++; new_board[i][j + 1] = ' ';}
                    if(new_board[i + 1][j] != ' ') {answer++; new_board[i + 1][j] = ' ';}
                    if(new_board[i + 1][j + 1] != ' ') {answer++; new_board[i + 1][j + 1] = ' ';}
                    check = true;
                }
            }
        }
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (new_board[i][j] != ' ') continue;
                for (int k = i - 1; k >= 0; --k) {
                    if (new_board[k][j] == ' ') continue;
                    swap(new_board[i][j], new_board[k][j]); break;
                }
            }
        }
        board = new_board;
        if(check == false) break;
    }
    return answer;
}