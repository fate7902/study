#include <string>
#include <vector>

using namespace std;

int solution(int storey) {
    int answer = 0;
    while(storey > 0){
        int now = storey % 10;
        int next = (storey % 100) / 10;
        storey /= 10;
        if((now == 5 && next >= 5) || now > 5){
            answer += (10 - now);
            storey++;
        }
        else answer += now;
    }
    return answer;
}