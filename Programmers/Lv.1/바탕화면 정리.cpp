#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> wallpaper) {
    int minX = 51, maxX = -1, minY = 51, maxY = -1;
    int x = 0;
    for(const auto& s : wallpaper){
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '#'){
                minX = minX < x ? minX : x;
                maxX = maxX > x + 1 ? maxX : x + 1;
                minY = minY < i ? minY : i;
                maxY = maxY > i + 1 ? maxY : i + 1;
            }
        }
        x++;
    }
    return { minX, minY, maxX, maxY };
}