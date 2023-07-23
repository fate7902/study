#include <string>
#include <vector>

using namespace std;

int solution(string s) {    
    int len = s.size();
    int answer = len;
    for(int i = 1; i <= len / 2; ++i){
        string newString = "", prev = "";
        int wordCnt = 0;
        int pos = 0;
        while(pos < len){
            string nowWord = s.substr(pos, i);
            if(prev == ""){
                prev = nowWord;
                wordCnt++;
            }
            else{
                if(prev == nowWord) wordCnt++;
                else{
                    if(wordCnt != 1) newString += to_string(wordCnt);
                    newString += prev;
                    prev = nowWord;
                    wordCnt = 1;
                }
            }
            pos += i;            
        }
        if(wordCnt != 1) newString += to_string(wordCnt);
        newString += prev;
        answer = answer < newString.size() ? answer : newString.size();
    }
    return answer;
}