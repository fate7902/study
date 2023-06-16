#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<int, double>& a, const pair<int, double>& b){
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}

vector<int> solution(int N, vector<int> stages) {
    vector<double> now(N + 1, 0);
    vector<double> total(N + 1, 0);
    for(auto& a : stages) {        
        if(a <= N + 1){
            if(a <= N) now[a]++;            
            a = a == N + 1 ? N : a;
            for(int i = 1; i <= a; ++i) total[i]++;
        }            
    }
    vector<pair<int, double>> fail;
    for(int i = 1; i <= N; ++i) {
        if(total[i] != 0) fail.emplace_back(make_pair(i, now[i] / total[i]));
        else fail.emplace_back(make_pair(i, 0));        
    }
    sort(fail.begin(), fail.end(), cmp);
    vector<int> answer;
    for(const auto& p : fail){
        answer.emplace_back(p.first);
    }
    return answer;
}