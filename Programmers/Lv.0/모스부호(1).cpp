#include <string>
#include <vector>
#include <cstring>

using namespace std;

string morse[26] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-",
        ".--", "-..-", "-.--", "--.." };

string solution(string letter) {
    string answer = "";
    char* ptr = strtok(const_cast<char*>(letter.c_str()), " ");
    while (ptr != NULL) {
        int index = 0;
        for (int i = 0; i < 26; i++) {
            if (morse[i] == ptr) {
                index = i;
                break;
            }
        }
        answer += (index + 'a');
        ptr = strtok(NULL, " ");
    }    
    return answer;
}