#include <string>
#include <vector>

using namespace std;

int solution(string t, string p) {    
    long long int num = stoll(p);
    int len = p.size();
    int answer = 0;
    for(int i = 0; i <= t.size() - len; ++i){
        if(stoll(t.substr(i, len)) <= num) answer++;
    }    
    return answer;
}