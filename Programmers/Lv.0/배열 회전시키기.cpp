#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> numbers, string direction) {
    if(direction.compare("left") == 0){
        int tmp = numbers[0];
        for(int i = 0; i < numbers.size() - 1; i++){
            numbers[i] = numbers[i + 1];
        }
        numbers[numbers.size() - 1] = tmp;
    }else{
        int tmp = numbers[numbers.size() - 1];
        for(int i = numbers.size() - 1; i > 0; i--){
            numbers[i] = numbers[i - 1];
        }
        numbers[0] = tmp;
    }
    return numbers;
}

// <algorithm>의 rotate()함수도 이용가능