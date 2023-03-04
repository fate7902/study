#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    short array[26] = {0, };
    for(int i = 0; i < s.size(); i++){
        array[s[i] - 'a']++;
    }
    string answer = "";
    for(int i = 0; i < 26; i++){
        if(array[i] == 1) answer += (i + 'a');
    }
    return answer;
}