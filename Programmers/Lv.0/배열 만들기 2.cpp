#include <string>
#include <vector>

using namespace std;

vector<int> solution(int l, int r) {
    vector<int> answer;
    for(int i = l; i <= r; ++i){
        bool check = true;
        int tmp = i;
        while(tmp > 0){
            int num = tmp % 10;
            if(num != 0 && num != 5){
                check = false;
                break;
            }
            tmp /= 10;
        }
        if(check) answer.emplace_back(i);
    }
    if(answer.empty()) answer.emplace_back(-1);
    return answer;
}