#include <iostream>
#include <string>
#include <stack>
using namespace std;

int solution(string s) {
    stack<char> stk;
    for(const auto& c : s) {
        if(stk.empty()) stk.emplace(c);
        else {
            if(stk.top() == c) stk.pop();
            else stk.emplace(c);
        }
    }    
    return stk.empty() ? 1 : 0;
}