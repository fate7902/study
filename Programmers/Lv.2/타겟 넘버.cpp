#include <string>
#include <vector>

using namespace std;

int answer = 0;

void DFS(vector<int> numbers, int target, int now, int index){
    if(index == numbers.size()){
        if(target == now) answer++;
    }
    else{
        DFS(numbers, target, now + numbers[index], index + 1);
        DFS(numbers, target, now - numbers[index], index + 1);
    }
}

int solution(vector<int> numbers, int target) {
    DFS(numbers, target, 0, 0);
    return answer;
}