#include <string>
#include <vector>

using namespace std;

bool solution(string s) {
    bool answer = true;
    for(const auto& c : s){
        if(c < '0' || c > '9'){
            answer = false;
            break;
        }
    }
    
    answer = (s.size() == 4 || s.size() == 6) ? answer : false;
    
    return answer;
}