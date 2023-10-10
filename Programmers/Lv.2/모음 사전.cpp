#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

map<char, int> number = {{'A', 1}, {'E', 2}, {'I', 3}, {'O', 4}, {'U', 5}};

int solution(string word) {
    int answer = 0, exponent = 4;    
    
    for(const auto& c : word){
        int interval = number[c] - 1;
        answer += 1;
        if(0 != interval){
            int calibrate = 0;
            for(int i = 0; i <= exponent; ++i) calibrate += pow(5, i);
            answer += (calibrate * interval);            
        }
        exponent--;
    }
    
    return answer;
}