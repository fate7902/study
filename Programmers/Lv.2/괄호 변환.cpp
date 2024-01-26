#include <string>
#include <vector>
#include <stack>

using namespace std;

void DivideString(string p, string& u, string& v){
    int len = p.size();
    int leftNum = 0, rightNum = 0;
    for(int i = 0; i < len; ++i){
        if(p[i] == '(') leftNum++;
        else rightNum++;
        if(leftNum == rightNum){
            u = p.substr(0, i + 1);
            v = p.substr(i + 1);
            break;
        }
    }
}

bool IsCorrect(string& u){
    stack<char> stk;
    for(const auto& c : u){
        if(c == '(') stk.emplace(c);
        else{
            if(!stk.empty() && stk.top() == '(') stk.pop();
            else stk.emplace(c);
        }
    }
    return stk.empty() ? true : false;
}

string Conversion(string& p){
    if(p.size() == 0) return "";
    string u, v;
    DivideString(p, u, v);
    if(IsCorrect(u)) return u + Conversion(v);
    else{
        string reverseU = u.substr(1, u.size() - 2);
        for(auto& c : reverseU){
            c = c == '(' ? ')' : '(';
        }
        return "(" + Conversion(v) + ")" + reverseU;
    }
}

string solution(string p) {
    return Conversion(p);
}