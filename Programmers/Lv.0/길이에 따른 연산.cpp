#include <string>
#include <vector>

using namespace std;

int solution(vector<int> num_list) {    
    return [&]{
        int len = num_list.size();
        int answer = len > 10 ? 0 : 1;        
        for(const auto& a : num_list){
            if(len > 10) answer += a;
            else answer *= a;
        }
        return answer;
    }();
}