#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> name, vector<int> yearning, vector<vector<string>> photo) {
    vector<int> answer;
    for(const auto& v : photo){
        int point = 0;
        for(int i = 0; i < v.size(); ++i){
            auto iter = find(name.begin(), name.end(), v[i]);
            if(iter != name.end()){
                point += yearning[iter - name.begin()];
            }
        }
        answer.emplace_back(point);
    }
    return answer;
}