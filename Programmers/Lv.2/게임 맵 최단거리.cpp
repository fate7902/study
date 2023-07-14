#include <vector>
#include <queue>
using namespace std;

int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int solution(vector<vector<int>> maps) {        
    int n = maps.size(), m = maps[0].size();
    vector<vector<bool>> visit(n, vector<bool>(m, false));
    visit[0][0] = true;
    vector<vector<int>> distance(n--, vector<int>(m--, 1));    
    queue<pair<int, int>> q;
    q.emplace(make_pair(0, 0));        
    while(!q.empty()){
        pair<int, int> pos = q.front();
        int row = pos.first, col = pos.second;
        q.pop();
        
        if(row == n && col == m) return distance[row][col];
        
        for(int i = 0; i < 4; ++i){
            int next_row = row + dir[i][0];
            int next_col = col + dir[i][1];
            if(next_row <= n && next_row >= 0 && next_col <= m && next_col >= 0){
                if(maps[next_row][next_col] == 1 && distance[next_row][next_col] == 1){
                    distance[next_row][next_col] =  distance[row][col] + 1;
                    q.emplace(make_pair(next_row, next_col));
                }
            }
        }
    }
    return -1;
}