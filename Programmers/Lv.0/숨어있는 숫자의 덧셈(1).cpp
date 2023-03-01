#include <string>
#include <vector>

using namespace std;

int solution(string my_string) {
    int answer = 0;
    for(const auto& c : my_string){
        if(c > 48 && c < 58){
            answer += (c - 48);
        }
    }    
    return answer;
}

// 아스키코드 10진수표시 보다 문자로 표현하는 게 알기 쉬움
// 48 = '0' 과 같은 식으로