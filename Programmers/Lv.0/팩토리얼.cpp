#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int sum = 1, cnt = 1;
    while(true){
        for(int i = 1; i <= cnt; i++){
            sum *= i;
        }
        if(n >= sum) {
            cnt++;
            sum = 1;
        }else{
            return cnt - 1;
        }
    }
}