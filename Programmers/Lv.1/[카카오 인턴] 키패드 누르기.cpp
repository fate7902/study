#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

string solution(vector<int> numbers, string hand) {
    map<int, pair<int, int>> m = { {1, {0, 3}}, {2, {1, 3}}, {3, {2, 3}},
                                 {4, {0, 2}}, {5, {1, 2}}, {6, {2, 2}},
                                 {7, {0, 1}}, {8, {1, 1}}, {9, {2, 1}},
                                {0, {1, 0}} };
    string answer = "";
    int left = -1, right = -1;
    for(const auto& a : numbers){
        if(a == 1 || a == 4 || a == 7) {answer += "L"; left = a;}
        else if(a == 3 || a == 6 || a == 9) {answer += "R"; right = a;}
        else {
            int left_dis = abs(m[left].first - m[a].first) + abs(m[left].second - m[a].second);
            int right_dis = abs(m[right].first - m[a].first) + abs(m[right].second - m[a].second);
            if(left_dis == right_dis){
                if(hand == "left") {answer += "L"; left = a;}
                else {answer += "R"; right = a;}
            }
            else{
                if(left_dis < right_dis) {answer += "L"; left = a;}
                else {answer += "R"; right = a;}
            }
        }
    }
    return answer;
}