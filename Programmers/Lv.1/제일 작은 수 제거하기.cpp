#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> temp;
    temp = arr;
    sort(temp.begin(), temp.end());
    vector<int> answer;
    if(temp.size() == 1) answer.emplace_back(-1);
    else {
        answer = arr;
        answer.erase(remove(answer.begin(), answer.end(), temp[0]), answer.end());
    }
    return answer;
}