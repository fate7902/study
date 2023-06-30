#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<int , string> m = {{0, "1"},{1, "2"},{2, "4"}};

string solution(int n) {
    string answer = "";
    while(n > 0){        
        answer += m[--n % 3];
        n /= 3;
    }
    reverse(answer.begin(), answer.end());
    return answer;
}