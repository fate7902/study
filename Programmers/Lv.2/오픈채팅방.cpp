#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<vector<string>> vec;
    map<string, string> m;
    for(const auto& s : record){
        stringstream ss(s);
        string type, id, name;
        ss >> type >> id >> name;
        if(type != "Change"){
            if(type == "Enter") m[id] = name;
            vector<string> tmp = {type, id, m[id]};
            vec.emplace_back(tmp);
        }
        else{
            m[id] = name;
            for(auto& v : vec){
                if(v[1] == id) v[2] = m[id];
            }
        }
    }
    vector<string> answer;
    for(const auto& v : vec){
        string msg = m[v[1]] + "님이 ";
        msg += v[0] == "Enter" ? "들어왔습니다." : "나갔습니다.";
        answer.emplace_back(msg);
    }
    return answer;
}