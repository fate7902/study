#include <string>
#include <vector>

using namespace std;

int answer = 0;

void BFS(int k, vector<vector<int>> dungeons, int cnt){
    if(dungeons.empty()) answer = answer < cnt ? cnt : answer;
    else{
        for(int i = 0; i < dungeons.size(); ++i){
            if(dungeons[i][0] <= k){
                k -= dungeons[i][1];
                cnt++;
                vector<vector<int>> tmp = dungeons;
                tmp.erase(tmp.begin() + i);
                BFS(k, tmp, cnt);
                k += dungeons[i][1];
                cnt--;
            }
            else{
                vector<vector<int>> tmp = dungeons;
                tmp.erase(tmp.begin() + i);
                BFS(k, tmp, cnt);
            }
        }
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    BFS(k, dungeons, answer);
    return answer;
}