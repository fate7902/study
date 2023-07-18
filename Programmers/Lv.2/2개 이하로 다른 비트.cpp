#include <string>
#include <vector>
#include <bitset>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for(const auto& a : numbers){
        if(a % 2 == 0) answer.emplace_back(a + 1);
        else{
            bitset<50> origin(a);
            string str = origin.to_string();
            int len = str.size() - 1;
            for(int i = len; i >= 0; --i){
                if(str[i] == '0'){
                    str[i] = '1';
                    if(i != len) str[i + 1] = '0';
                    break;
                }
            }
            bitset<50> goalNum(str);
            answer.emplace_back(goalNum.to_ullong());
        }
    }
    return answer;
}