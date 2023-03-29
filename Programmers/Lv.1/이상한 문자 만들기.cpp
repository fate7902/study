#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    int pos = 0;
    for(int i = 0; i < s.size(); ++i){
        if(s[i] == ' '){
            pos = 0;
            continue;
        }
        s[i] = pos % 2 == 0 ? toupper(s[i]) : tolower(s[i]);
        pos++;
    }
    return s;
}