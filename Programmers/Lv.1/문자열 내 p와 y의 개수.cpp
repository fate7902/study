#include <string>
#include <iostream>
#include <cctype>
using namespace std;

bool solution(string s) {
    short num[26] = { 0 };
    for(int i = 0; i < s.size(); ++ i){
        s[i] = tolower(s[i]);
        num[s[i] - 'a']++;
    }
    bool answer = true;
    if(num['p' - 'a'] != 0 || num['y' - 'a'] != 0){
        if(num['p' - 'a'] != num['y' - 'a']){
            answer = false;
        }
    }

    return answer;
}