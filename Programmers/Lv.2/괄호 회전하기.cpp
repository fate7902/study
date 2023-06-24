#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(string s) {
    int answer = 0;
    int len = s.size();
    for(int i = 0; i < len; ++i){
        string a = s.substr(0, i);
        string b = s.substr(i, len - i);
        string str = b + a;
        stack<char> stk;
        for(const auto& c : str){
            if(stk.empty()) stk.emplace(c);
            else{
                if((c == ')' && stk.top() == '(') || 
                   (c == '}' && stk.top() == '{') || 
                   c == ']' && stk.top() == '[') {
                    stk.pop();
                }
                else stk.emplace(c);
            }
        }
        if(stk.empty()) answer++;
    }
    return answer;
}