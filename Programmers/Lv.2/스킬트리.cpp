#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>

using namespace std;

map<char, int> num;
int cnt = 1;

bool cmp(const char& a, const char& b){
    return num[a] < num[b];
}

int solution(string skill, vector<string> skill_trees) {   
    for(const auto& c : skill) num[c] = cnt++;
    int answer = 0;
    for(auto& s : skill_trees){
        s = regex_replace(s, regex("[^" + skill + "]"), "");
		string tmp(s);
		sort(tmp.begin(), tmp.end(), cmp);
		if (tmp == s && num[*s.rbegin()] == s.size()) answer++;
    }
    return answer;
}