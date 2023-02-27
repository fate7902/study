#include <string>
#include <vector>

using namespace std;

int solution(int slice, int n) {
    int answer = 1;
     while(true){
         if((slice * answer) / n >= 1) return answer;
         answer++;
     }
}