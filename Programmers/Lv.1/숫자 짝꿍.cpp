#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string X, string Y) {
    vector<int> arrX(10, 0);
    vector<int> arrY(10, 0);
    for(const auto& a : X) arrX[a - '0']++;
    for(const auto& a : Y) arrY[a - '0']++;
    string answer = "";
    for(int i = 0; i < 10; ++i){
        answer += string(arrX[i] > arrY[i] ? arrY[i] : arrX[i], i + '0');
    }
    sort(answer.begin(), answer.end(), greater<int>());
    if(answer.size() == 0) answer = "-1";
    else if(count(answer.begin(), answer.end(), '0') == answer.size()) answer = "0";
    return answer;
}