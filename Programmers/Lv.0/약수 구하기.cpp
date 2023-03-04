#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n) {
    vector<int> answer;
    for(int i = 1; i <= n; i++) {
        if(0 == n % i) answer.emplace_back(i);
    }
    return answer;
}