#include <string>
#include <vector>

using namespace std;

string solution(int age) {
    string answer = "";
    string my_age = to_string(age);
    for(int i = 0; i < my_age.size(); i++){
        answer += (my_age[i] - '0' + 'a');
    }
    return answer;
}