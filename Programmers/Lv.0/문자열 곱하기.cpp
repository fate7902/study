#include <string>
#include <vector>

using namespace std;

string solution(string my_string, int k) {    
    return [&]{
        string answer = "";
        while(k--){
            answer += my_string;
        }
        return answer;
    }();
}