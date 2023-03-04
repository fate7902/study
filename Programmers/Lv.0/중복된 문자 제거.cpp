#include <string>
#include <vector>

using namespace std;

string solution(string my_string) {    
    string answer = "";
    for(int i = 0; i < my_string.size(); i++){
        bool flag = false;
        for(int j = 0; j < i; j++){
            if(my_string[i] == my_string[j]){
                flag = true;
                break;
            }
        }
        if(flag == false) answer += my_string[i];
    }
    return answer;
}

// answer에 my_string의 문자가 있는지 확인 후 없으면 넣는 방식도 존재