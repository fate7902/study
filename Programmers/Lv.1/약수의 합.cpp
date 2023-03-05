#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(int n) {
    int answer = 0;
    set<int> num;
    for(int i = 1; i <= n / 2; ++i){
        if(n % i != 0) continue;
        num.insert(i);
        if(n / i == i) continue;
        num.insert(n / i);        
    }
    for(const auto& n : num){
        answer += n;
    }
    if(n < 2) return n;
    return answer;
}