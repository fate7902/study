#include <string>
#include <vector>

using namespace std;

int solution(int order) {
    string str = to_string(order);
    int answer = 0;
    for(int i = 0; i < str.size(); i++){
        if(str[i] - '0' != 0){
            if((str[i] - '0') % 3 == 0) answer++;
        }
    }
    return answer;
}