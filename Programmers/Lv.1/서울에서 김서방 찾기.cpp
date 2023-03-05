#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> seoul) {
    int x = find(seoul.begin(), seoul.end(), "Kim") - seoul.begin();
    string answer = "김서방은 ";
    answer += to_string(x) + "에 있다";
    return answer;
}