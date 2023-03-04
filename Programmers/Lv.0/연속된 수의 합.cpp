#include <string>
#include <vector>

using namespace std;

vector<int> solution(int num, int total) {
    vector<int> answer;
    int temp = total / num;
    int dis = (num - 1) / 2;
    if(num % 2 == 0){        
        for(int i = temp - dis; i <= temp + dis + 1; i++){
            answer.emplace_back(i);
        }
    }else{        
        for(int i = temp - dis; i < temp + dis + 1; i++){
            answer.emplace_back(i);
        }
    }    
    return answer;
}