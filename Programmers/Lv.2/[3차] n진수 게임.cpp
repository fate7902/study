#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void changeString(string& origin, int n, int num){
    string str = "";
    while(num > 0){
        int remain = num % n;        
        if(remain > 9) str += ('A' + (remain - 10));
        else str += to_string(num % n);
        num /= n;
    }
    reverse(str.begin(), str.end());
    origin += str;
}

string solution(int n, int t, int m, int p) {
    string answer = "", str = "0";
    int start = 1;
    while(t * m > str.size()) changeString(str, n, start++);
    for(int i = 0; i < t; ++i) answer += str[i * m + p - 1];
    return answer;
}