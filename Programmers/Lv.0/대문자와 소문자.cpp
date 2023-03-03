#include <string>
#include <vector>

using namespace std;

string solution(string my_string) {
    string answer = "";
    for(int i = 0; i < my_string.size(); i++){
        if('a' <= my_string[i] && my_string[i] <= 'z'){
            answer += (my_string[i] + ('A' - 'a'));
        }else{
            answer += (my_string[i] - ('A' - 'a'));
        }
    }
    return answer;
}

// <cctype>에 있는 islower() 와 tolower() 계열도 사용 가능