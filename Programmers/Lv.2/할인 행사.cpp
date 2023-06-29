#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int len = discount.size();
    map<string, int> possible;
    int answer = 0;
    for(int i = 0; i < len; ++i){
        if(i < 9) possible[discount[i]]++;
        else{
            if(i > 9) possible[discount[i - 10]]--;
            possible[discount[i]]++;
            bool flag = true;
            for(int j = 0; j < want.size(); ++j){
                if(possible[want[j]] < number[j]) {
                    flag = false;
                    break;
                }
            }
            if(flag) answer++;
        }
    }
    return answer;
}