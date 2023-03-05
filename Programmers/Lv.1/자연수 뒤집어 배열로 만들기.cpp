#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(long long n) {
    string s(to_string(n));
    reverse(s.begin(), s.end());
    
    vector<int> answer;    
    for(int i = 0; i < s.size(); ++i){
        answer.emplace_back(s[i] - '0');
    }
    return answer;
}