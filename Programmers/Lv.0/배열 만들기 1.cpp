#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int k) {
    vector<int> answer;
    int tmp = k;
    while(tmp <= n){
        answer.emplace_back(tmp);
        tmp += k;
    }
    return answer;
}