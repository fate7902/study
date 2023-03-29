#include <string>
#include <vector>
#include <cctype>

using namespace std;

string solution(string s, int n) {
    for(int i = 0; i < s.size(); ++i){
        if(s[i] == ' ') continue;
        if(islower(s[i])){
            if(s[i] + n > 'z') s[i] += (n - 26);
            else s[i] += n;
        }else{            
            if(s[i] + n > 'Z') s[i] += (n - 26);
            else s[i] += n;
        }
    }
    return s;
}