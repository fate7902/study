#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    int len = progresses.size();
    vector<int> day(len, 0);
    for(int i = 0; i < len; ++i){
        int left = 100 - progresses[i];
        int estime = left % speeds[i] == 0 ? left / speeds[i] : left / speeds[i] + 1;
        day[i] = estime;
    }
    vector<int> answer;
    int prev = 0;
    for(int i = 1; i < len; ++i){
        if(day[i] > day[prev]){
            answer.emplace_back(i - prev);
            prev = i;
        }
    }
    answer.emplace_back(len - prev);
    return answer;
}