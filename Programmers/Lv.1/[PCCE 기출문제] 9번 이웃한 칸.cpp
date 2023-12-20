#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<string>> board, int h, int w) {
    int answer = 0;
    string color = board[h][w];
    
    if(w - 1 >= 0 && board[h][w - 1] == color) answer++;
    if(w + 1 < board.size() && board[h][w + 1] == color) answer++;
    if(h - 1 >= 0 && board[h - 1][w] == color) answer++;
    if(h + 1 < board.size() && board[h + 1][w] == color) answer++;
    
    return answer;
}