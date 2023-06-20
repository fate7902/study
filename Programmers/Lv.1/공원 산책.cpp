#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> park, vector<string> routes) {
    int x = -1, y = -1;    
    int n = park.size();
    int m = park[0].size();
    for (int i = 0; i < n; ++i) {
        auto pos = park[i].find('S');
        if (pos != string::npos) {
            x = i;
            y = static_cast<int>(pos);
            break;
        }
    }
    
    for(const auto& s : routes){
        int step = s[2] - '0';
        bool flag = false;
        switch(s[0]){
            case 'N':
                for(int i = 1; i <= step; ++i){
                    if(x - i >= 0 && park[x - i][y] == 'X'){
                        flag = true;
                        break;
                    }
                }
                if(flag || x - step < 0) continue;
                x -= step;
                break;
            case 'S':
                for(int i = 1; i <= step; ++i){
                    if(x + i < n && park[x + i][y] == 'X'){
                        flag = true;
                        break;
                    }
                }
                if(flag || x + step >= n) continue;
                x += step;
                break;
            case 'W':
                for(int i = 1; i <= step; ++i){
                    if(y - i >= 0 && park[x][y - i] == 'X'){
                        flag = true;
                        break;
                    }
                }
                if(flag || y - step < 0) continue;
                y -= step;
                break;
            case 'E':
                for(int i = 1; i <= step; ++i){
                    if(y + i < m && park[x][y + i] == 'X'){
                        flag = true;
                        break;
                    }
                }
                if(flag || y + step >= m) continue;
                y += step;
                break;
        }
    }
    return { x, y };
}