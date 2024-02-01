#include <string>
#include <vector>
#include <queue>
#include <cctype>
#include <algorithm>

using namespace std;

long long answer = 0;

long long CalBaesdOnOper(long long a, long long b, char oper){
    switch(oper){
        case '*': return a * b;
        case '+': return a + b;
        case '-': return a - b;
    }
    return -1;
}

void Calculate(queue<long long>& num, queue<char>& op, vector<bool>& usedOper){
    if(op.empty()){
        long long result = num.front();
        if(result < 0) result *= -1;
        answer = answer < result ? result : answer;
    }else{
        for(int i = 0; i < usedOper.size(); ++i){
            if(usedOper[i]) continue;
            char currentOper = i == 0 ? '*' : (i == 1 ? '+' : '-');
            queue<long long> number, tempNum = num;
            queue<char> oper, tempOp = op;
            while(!tempOp.empty()){
                if(tempOp.front() != currentOper){
                    number.emplace(tempNum.front());
                    tempNum.pop();
                    oper.emplace(tempOp.front());
                    tempOp.pop();
                }else{
                    long long a = tempNum.front();
                    tempNum.pop();
                    long long b = tempNum.front();
                    tempNum.front() = CalBaesdOnOper(a, b, tempOp.front());
                    tempOp.pop();
                }
            }
            number.emplace(tempNum.front());
            usedOper[i] = true;
            Calculate(number, oper, usedOper);
            usedOper[i] = false;
        }
    }
}

long long solution(string expression) {
    int len = expression.size(), index = 0;
    queue<long long> number;
    queue<char> oper;
    for(int i = 0; i < len; ++i){
        if(isdigit(expression[i]) == 0){
            oper.emplace(expression[i]);
            number.emplace(stoi(expression.substr(index, i - index)));
            index = i + 1;
        }else if(i == len - 1) number.emplace(stoi(expression.substr(index)));
    }
    
    vector<bool> usedOper(3, false);
    Calculate(number, oper, usedOper);    
    return answer;
}