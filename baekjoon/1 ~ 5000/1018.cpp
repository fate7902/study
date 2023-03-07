#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    string temp;
    vector<string> board;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        board.emplace_back(temp);
    }

    int cntW, cntB;
    int answer = n * m;
    for (int x = 0; x <= n - 8; x++) {
        for (int y = 0; y <= m - 8; y++) {
            cntW = 0;
            cntB = 0;
            for (int i = x; i < x + 8; i++) {
                for (int j = y; j < y + 8; j++) {
                    if ((i + j) % 2 == 0) {
                        if (board[i][j] == 'B') cntB++;
                        else cntW++;
                    }
                    else {
                        if (board[i][j] == 'W') cntB++;
                        else cntW++;
                    }
                }
            }
            answer = min(answer, cntB);
            answer = min(answer, cntW);
        }
    }
    
    cout << answer;
}