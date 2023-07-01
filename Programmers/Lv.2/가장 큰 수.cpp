#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const int& a, const int& b){
    string strA = to_string(a);
    string strB = to_string(b);
    return strA + strB > strB + strA;
}

string solution(vector<int> numbers) {
    sort(numbers.begin(), numbers.end(), cmp);
    string answer = "";
    for(const auto& a : numbers) answer += to_string(a);
    if(answer.size() == count(answer.begin(), answer.end(), '0')) answer = "0";
    return answer;
}