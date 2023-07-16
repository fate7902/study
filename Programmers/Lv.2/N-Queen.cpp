#include <string>
#include <vector>

using namespace std;

int answer = 0;

void search(vector<vector<bool>>& map, int row){
    if(row == map.size()) answer++;
    else{
        for(int i = 0; i < map.size(); ++i){
            if(map[row][i]){
                vector<vector<bool>> tmp(map);
                for(int j = 0; j < map.size(); ++j) map[row][j] = false;                
                for(int j = row + 1; j < map.size(); ++j) {
                    map[j][i] = false;
                    if(i - (j - row) >= 0) map[j][i - (j - row)] = false;
                    if(i + (j - row) < map.size()) map[j][i + (j - row)] = false;
                }
                search(map, row + 1);
                map = tmp;
            }
        }
    }
}

int solution(int n) {
    vector<vector<bool>> map(n, vector<bool>(n, true));
    search(map, 0);
    return answer;
}