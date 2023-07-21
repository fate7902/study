#include <string>
#include <vector>

using namespace std;

bool check(vector<string>& place, int x, int y){
    // 우측 방향 체크
    for(int i = y + 1; i <= y + 2; ++i){
        if(i >= 5) break;
        if(place[x][i] == 'X') break;
        if(place[x][i] == 'P') return false;
    }
    // 좌측 방향 체크
    for(int i = y - 1; i >= y - 2; --i){
        if(i < 0) break;
        if(place[x][i] == 'X') break;
        if(place[x][i] == 'P') return false;
    }
    // 아래 방향 체크
    for(int i = x + 1; i <= x + 2; ++i){
        if(i >= 5) break;
        if(place[i][y] == 'X') break;
        if(place[i][y] == 'P') return false;
    }
    // 위 방향 체크
    for(int i = x - 1; i >= x - 2; --i){
        if(i < 0) break;
        if(place[i][y] == 'X') break;
        if(place[i][y] == 'P') return false;
    }
    // 대각선 방향 체크
    if(x + 1 < 5 && y + 1 < 5 && place[x + 1][y + 1] == 'P' && (place[x + 1][y] == 'O' || place[x][y + 1] == 'O')) return false;
    if(x + 1 < 5 && y - 1 >= 0 && place[x + 1][y - 1] == 'P' && (place[x + 1][y] == 'O' || place[x][y - 1] == 'O')) return false;
    if(x - 1 >= 0 && y + 1 < 5 && place[x - 1][y + 1] == 'P' && (place[x - 1][y] == 'O' || place[x][y + 1] == 'O')) return false;
    if(x - 1 >= 0 && y - 1 >= 0 && place[x - 1][y - 1] == 'P' && (place[x - 1][y] == 'O' || place[x][y - 1] == 'O')) return false;
    
    return true;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    for(int i = 0; i < 5; ++i){
        vector<pair<int, int>> people;        
        for(int x = 0; x < 5; ++x){
            for(int y = 0; y < 5; ++y){
                if(places[i][x][y] == 'P'){
                    if(!check(places[i], x, y)){
                        answer.emplace_back(0);
                        x = 5; y = 5;
                    }
                }                
            }
        }
        if(answer.size() == i) answer.emplace_back(1);
    }
    return answer;
}