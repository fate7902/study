#include <string>
#include <vector>

using namespace std;

int solution(int num, int k) {
    string str = to_string(num);
    int answer = 0;
    for(int i = 0; i < str.size(); i++){
        if(str[i] - '0' == k){
            answer = i + 1;
            break;
        }
    }
    if(answer == 0) answer = -1;
    return answer;
}