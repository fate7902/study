#include <string>
#include <vector>

using namespace std;

string solution(string s, string skip, int index) {
    string answer = "";
    for(auto& c : s){
        int tmp = index;
        while(tmp--){
            if(c + 1 <= 'z') c = c + 1;
            else c = 'a';
            if(skip.find(c) != string::npos) tmp++;
        }
        answer += c;
    }
    return answer;
}