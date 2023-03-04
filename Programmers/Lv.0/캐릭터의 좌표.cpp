#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> keyinput, vector<int> board) {
    vector<int> answer = { 0, 0 };
    int x = board[0] / 2;
    int y = board[1] / 2;
    for (int i = 0; i < keyinput.size(); i++) {
        if (keyinput[i].compare("left") == 0) {
            if (answer[0] - 1 >= -x) {
                answer[0] -= 1;
            }
        }
        else if (keyinput[i].compare("right") == 0) {
            if (answer[0] + 1 <= x) {
                answer[0] += 1;
            }
        }
        else if (keyinput[i].compare("up") == 0) {
            if (answer[1] + 1 <= y) {
                answer[1] += 1;
            }
        }
        else {
            if (answer[1] - 1 >= -y) {
                answer[1] -= 1;
            }
        }
    }
    return answer;
}