#include <string>
#include <vector>

using namespace std;

int solution(int i, int j, int k) {
    string str;
    for(int x = i; x <= j; x++){
        str += to_string(x);
    }
    int answer = 0;
    for(int x = 0; x < str.size(); x++){
        if(str[x] - '0' == k) answer++;
    }
    return answer;
}