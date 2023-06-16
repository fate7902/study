#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> one = { 1, 2, 3, 4, 5 };
    vector<int> two = { 2, 1, 2, 3, 2, 4, 2, 5 };
    vector<int> three = { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 };
    vector<int> num(3, 0);
    for(int i = 0; i < answers.size(); ++i){
        if(one[i % one.size()] == answers[i]) num[0]++;
        if(two[i % two.size()] == answers[i]) num[1]++;
        if(three[i % three.size()] == answers[i]) num[2]++;
    }
    int cut = *max_element(num.begin(), num.end());
    vector<int> answer;
    for(int i = 0; i < num.size(); ++i){
        if(cut == num[i]) answer.emplace_back(i + 1);
    }
    return answer;
}