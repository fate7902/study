#include <string>
#include <vector>

using namespace std;

string solution(string cipher, int code) {
    string answer = "";
    int num = code;
    while(cipher.size() >= num){
        answer += cipher[num - 1];
        num += code;
    }
    return answer;
}