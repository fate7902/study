#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer;
    for(const auto& a : arr){
        if(answer.size() > 0){
            if(a != answer[answer.size() - 1]){
                answer.emplace_back(a);
            }
        }else{
            answer.emplace_back(a);
        }
    }
    return answer;
}