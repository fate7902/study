#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 1;
    while(true){
        if(0 < (answer * 7) / n) return answer;
        answer++;
    }    
}