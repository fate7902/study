#include <string>
#include <vector>

using namespace std;

vector<string> solution(vector<string> strArr) {
    return [&]{
        vector<string> answer;
        for(const auto& s : strArr){
            if(s.find("ad") == string::npos)
                answer.emplace_back(s);
        }
        return answer;
    }();
}