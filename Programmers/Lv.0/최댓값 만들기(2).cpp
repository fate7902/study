#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers) {
    int answer = -1000000000;
    for(int i = 0; i < numbers.size(); i++){
        for(int j = 0; j < numbers.size(); j++){
            if(i != j){
                if(numbers[i] * numbers[j] > answer) {
                    answer = numbers[i] * numbers[j];
                }
            }
        }
    }
    return answer;
}

// 최댓값이 음수인 경우가 있다