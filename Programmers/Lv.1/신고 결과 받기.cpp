#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    unordered_map<string, int> report_num;
    unordered_map<string, int> mail_num;
    unordered_map<string, vector<string>> report_list;
    for(const auto& s : id_list) {        
        report_num[s] = 0;
        mail_num[s] = 0;
        report_list[s] = vector<string>();
    }
    for(const auto& s : report){
        auto index = s.find(' ');
        string name = s.substr(0, index);
        string report_name = s.substr(index + 1);
        if(find(report_list[name].begin(), report_list[name].end(), report_name) == report_list[name].end()){  
            report_num[report_name]++;
            report_list[name].emplace_back(report_name);
        }
    }
    for(const auto& m : report_num){
        if(m.second >= k){            
            for(const auto& l : report_list){
                if(find(l.second.begin(), l.second.end(), m.first) != l.second.end()){
                    mail_num[l.first]++;
                }
            }
        }
    }
    vector<int> answer;
    for(const auto& s : id_list) answer.emplace_back(mail_num[s]);
    return answer;
}