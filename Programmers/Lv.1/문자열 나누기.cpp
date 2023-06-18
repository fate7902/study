#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int answer = 0;
    char check = '0';
    int cnt = 0;
    for(const auto& c : s){
        if(check == '0') {
            check = c;
            cnt++;
            continue;
        }
        if(check == c) cnt++;
        else{
            cnt--;
            if(cnt == 0) {
                answer++;
                check = '0';
            }
        }
    }
    if(cnt != 0) answer++;
    return answer;
}