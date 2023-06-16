#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int n) {
    int answer = 0;
    for(int i = 2; i <= n; ++i){
        bool flag = true;
        int tmp = sqrt(i);
        for(int a = 2; a <= tmp; ++a){
            if(i % a == 0){
                flag = false;
                break;
            }
        }
        if(flag) answer++;
    }
    return answer;
}