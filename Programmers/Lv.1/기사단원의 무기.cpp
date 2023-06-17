#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int number, int limit, int power) {
    int answer = 1;
    for(int i = 2; i <= number; ++i){
        int cnt = 2;
        int len = sqrt(i);
        for(int j = 2; j <= len; ++j){
            if(i % j == 0) { 
                cnt = i / j == j ? cnt + 1 : cnt + 2;
            }
        }
        if(cnt > limit) answer += power;
        else answer += cnt;
    }
    return answer;
}