#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b){
    return a.size() < b.size();
}

vector<int> solution(string s) {
    vector<vector<int>> arr;
    int len = s.size();
    string number = "";
    vector<int> tmp;
    for(const auto& c : s){
        if(isdigit(c)) number += c;
        else if(c == ',' && !number.empty()){
            tmp.emplace_back(stoi(number));
            number = "";
        }
        else if(c == '}' && !number.empty()){
            tmp.emplace_back(stoi(number));
            number = "";
            arr.emplace_back(tmp);
            tmp.clear();
        }
    }
    sort(arr.begin(), arr.end(), cmp);
    vector<int> answer;
    for(const auto& v : arr){
        for(const auto& a : v) {
            if(find(answer.begin(), answer.end(), a) == answer.end()) answer.emplace_back(a);            
        }
    }
    return answer;
}