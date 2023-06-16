#include <vector>
#include <iostream>
using namespace std;

int solution(vector<int> nums) {
    int answer = 0;
    for(int i = 0; i < nums.size() - 2; ++i){
        for(int j = i + 1; j < nums.size() - 1; ++j){
            for(int k = j + 1; k < nums.size(); ++k){
                int tmp = nums[i] + nums[j] + nums[k];
                bool flag = true;
                for(int a = 2; a < tmp; ++a){
                    if(tmp % a == 0) {
                        flag = false;
                        break;
                    }
                }
                if(flag) answer++;
            }
        }
    }
    return answer;
}