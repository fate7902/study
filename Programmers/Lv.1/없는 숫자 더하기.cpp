#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers) {
    short num[10] = { 0 };
    for(const auto& n : numbers){
        num[n]++;
    }
    int answer = 0;
    for(int i = 0; i < 10; ++i){
        if(num[i] == 0) answer += i;
    }
    return answer;
}