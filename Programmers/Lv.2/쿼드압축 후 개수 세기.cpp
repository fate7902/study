#include <string>
#include <vector>

using namespace std;

int zeroCnt = 0, oneCnt = 0;
void compress(vector<vector<int>>& arr, int x, int y, int len){
    bool flag0 = false, flag1 = false;
    for(int i = x; i < x + len; ++i){
        for(int j = y; j < y + len; ++j){
            if(arr[i][j] == 0) flag0 = true;
            else flag1 = true;
            if(flag0 && flag1) {
                compress(arr, x, y, len / 2);
                compress(arr, x + len / 2, y, len / 2);
                compress(arr, x, y + len / 2, len / 2);
                compress(arr, x + len / 2, y + len / 2, len / 2);
                return;
            }
        }
    }
    if(flag0) zeroCnt++;
    else oneCnt++;
}

vector<int> solution(vector<vector<int>> arr) {
    int row = arr.size();
    compress(arr, 0, 0, row);
    return {zeroCnt, oneCnt};
}