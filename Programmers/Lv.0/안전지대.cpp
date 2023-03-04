#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    int len = board.size();
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (board[i][j] == 1) answer++;
            else {
                bool flag = false;
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && y >= 0 && x < len && y < len) {
                            if (board[x][y] == 1) {
                                answer++;
                                flag = true;
                                break;
                            }
                        }
                    }
                    if (flag == true) break;
                }
            }
        }
    }
    return len * len - answer;
}