#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s) {
    stack<char> stk;
    for(const auto& c : s){
        if(!stk.empty()){
            if(stk.top() == '(' && c == ')') stk.pop();
            else stk.emplace(c);
        }
        else stk.emplace(c);
    }
    return stk.empty() ? true : false;
}