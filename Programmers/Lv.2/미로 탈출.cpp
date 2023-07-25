#include <string>
#include <vector>
#include <queue>

using namespace std;

bool visit[100][100]{};
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int solution(vector<string> maps) {
    int answer = 0;
    int x = maps.size(), y = maps[0].size();
    pair<int, int> pos;
        
    bool flag = false;
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < y; ++j){
            if(maps[i][j] == 'S'){
                pos = {i, j};
                visit[i][j] = true;
                flag = true;
                break;
            }
        }
        if(flag) break;
    }
    
    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(pos, 0));
    while(flag){
        if(q.empty()) return -1;
        pair<pair<int, int>, int> current = q.front();
        int nowX = current.first.first, nowY = current.first.second;
        int time = current.second;
        q.pop();
        
        for(int i = 0; i < 4; ++i){
            int dx = nowX + dir[i][0];
            int dy = nowY + dir[i][1];
            
            if(dx >= 0 && dx < x && dy >= 0 && dy < y && !visit[dx][dy]){
                visit[dx][dy] = true;
                if(maps[dx][dy] == 'L'){
                    answer = time + 1;
                    pos = {dx, dy};
                    flag = false;
                    break;
                }
                else if(maps[dx][dy] != 'X') q.emplace(make_pair(make_pair(dx, dy), time + 1));
            }
            if(!flag) break;
        }
    }
    
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < y; ++j)
            visit[i][j] = false;
    }
    visit[pos.first][pos.second] = true;
    q = queue<pair<pair<int, int>, int>>();
    q.emplace(make_pair(pos, answer));
    while(true){
        if(q.empty()) return -1;
        pair<pair<int, int>, int> current = q.front();
        int nowX = current.first.first, nowY = current.first.second;
        int time = current.second;
        q.pop();
        
        for(int i = 0; i < 4; ++i){
            int dx = nowX + dir[i][0];
            int dy = nowY + dir[i][1];
            
            if(dx >= 0 && dx < x && dy >= 0 && dy < y && !visit[dx][dy]){
                visit[dx][dy] = true;
                if(maps[dx][dy] == 'E') return time + 1;
                else if(maps[dx][dy] != 'X') q.emplace(make_pair(make_pair(dx, dy), time + 1));
            }
        }
    }
}