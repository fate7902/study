#include <string>
#include <vector>

using namespace std;

int solution(string myString, string pat) {
    int answer = 0;    
    int idx = myString.find(pat);
    while (idx != string::npos) {
        answer++;
        idx = myString.find(pat, idx + 1);
    }    
    return answer;
}