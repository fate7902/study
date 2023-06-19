#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    vector<int> input;
    for(const auto& a : moves){
        for(int i = 0; i < board.size(); ++i){
            if(board[i][a - 1] != 0) {
                input.emplace_back(board[i][a - 1]);
                board[i][a - 1] = 0;
                break;
            }
        }
    }
    int answer = 0;
    for(int i = 0; i < static_cast<int>(input.size()) - 1; ++i){
        if(input[i] == input[i + 1]) {
            answer += 2;
            input.erase(input.begin() + i, input.begin() + i + 2);
            i = (i > 0) ? i - 2 : -1;
        }
    }
    return answer;
}