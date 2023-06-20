#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    map<char, int> term;
    for(const auto& s : terms){
        term[s[0]] = stoi(s.substr(2));
    }
    
    vector<int> answer;
    for (int i = 0; i < privacies.size(); ++i) {
        string day = privacies[i].substr(0, 10);
        int month = term[privacies[i].back()] + stoi(day.substr(5, 2));
        int year = (month % 12 == 0 ? month / 12 - 1 : month / 12) + stoi(day.substr(0, 4));
        month = month % 12 == 0 ? 12 : month % 12;
        string m = month < 10 ? "0" + to_string(month) : to_string(month);
        day.replace(5, 2, m);
        day.replace(0, 4, to_string(year));
        if (day <= today) answer.emplace_back(i + 1);
    }    
    return answer;
}