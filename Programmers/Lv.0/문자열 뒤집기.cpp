#include <string>
#include <vector>

using namespace std;

string solution(string my_string) {
    string answer = "";
    for(int i = my_string.size() - 1; i >= 0; i--){
        answer += my_string[i];
    }
    return answer;
}

// 알고리즘 헤더에 reverse(begin, end) 함수 존재