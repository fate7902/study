#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void search(vector<string>& maps, int& area, int i, int j){
    if(isdigit(maps[i][j])) { 
        area += (maps[i][j] - '0');
        maps[i][j] = 'X';
        if(i - 1 >= 0) search(maps, area, i - 1, j);
        if(j - 1 >= 0) search(maps, area, i, j - 1);
        if(i + 1 < maps.size()) search(maps, area, i + 1, j);
        if(j + 1 < maps[i].size()) search(maps, area, i, j + 1);
    }
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    for(int i = 0; i < maps.size(); ++i){
        for(int j = 0; j < maps[i].size(); ++j){
            if(isdigit(maps[i][j])){
                int area = 0;
                search(maps, area, i, j);
                answer.emplace_back(area);
            }
        }
    }
    sort(answer.begin(), answer.end());
    if(answer.empty()) answer.emplace_back(-1);
    return answer;
}