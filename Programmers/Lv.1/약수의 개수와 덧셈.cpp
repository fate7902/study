#include <string>
#include <vector>

using namespace std;

int solution(int left, int right) {
    int answer = 0;
    for(int i = left; i <= right; ++i){
        int cnt = 2;
        for(int j = 2; j < i; ++j){
            if(i % j == 0) cnt++;
        }
        if(cnt % 2 == 0) answer += i;
        else answer -= i;
    }
    if(left == 1) answer -= 2;
    return answer;
}