#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int n) {  
    int answer = 0;
    int start = n % 2 == 0 ? 2 : 1;
    if(n % 2 == 0){
        for(int i = start; i <= n; i += 2){
            answer += pow(i, 2);
        }
    }
    else{
        for(int i = start; i <= n; i += 2){
            answer += i;
        }
    }
    return answer;
}