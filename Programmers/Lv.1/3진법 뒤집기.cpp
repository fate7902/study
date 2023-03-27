#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    vector<int> arr;
    while(n){
        arr.emplace_back(n % 3);
        n /= 3;
    }
    
    int answer = 0;
    int value = 1;
    for(int i = arr.size() - 1; i >= 0; --i){
        answer += (arr[i] * value);
        value *= 3;
    }
    
    return answer;
}