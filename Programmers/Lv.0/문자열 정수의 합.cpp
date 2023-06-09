#include <string>
#include <vector>

using namespace std;

int solution(string num_str) {    
    return [&]{
        int answer = 0;
        for(int i = 0; i < num_str.size(); ++ i)
            answer += (num_str[i] - '0');
        return answer;
    }();
}