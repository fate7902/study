#include <string>
#include <vector>
#include <set>

using namespace std;

int arr[101][101]{};

void init(int row, int col){
    for(int i = 1; i <= row; ++i){
        for(int j = 1; j <= col; ++j){
            arr[i][j] = (i - 1) * col + j;
        }
    }
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    init(rows, columns);
    vector<int> answer;
    for(const auto& v : queries){
        set<int> number;
        int x1 = v[0], y1 = v[1];
        int x2 = v[2], y2 = v[3];
        int prev = arr[x1 + 1][y1];
        for(int i = y1; i <= y2; ++i){
            int tmp = arr[x1][i];
            arr[x1][i] = prev;
            prev = tmp;
            number.emplace(prev);
        }
        for(int i = x1 + 1; i <= x2; ++i){
            int tmp = arr[i][y2];
            arr[i][y2] = prev;
            prev = tmp;
            number.emplace(prev);
        }
        for(int i = y2 - 1; i >= y1; --i){
            int tmp = arr[x2][i];
            arr[x2][i] = prev;
            prev = tmp;
            number.emplace(prev);
        }
        for(int i = x2 - 1; i > x1; --i){
            int tmp = arr[i][y1];
            arr[i][y1] = prev;
            prev = tmp;
            number.emplace(prev);
        }
        answer.emplace_back(*number.begin());
    }
    return answer;
}