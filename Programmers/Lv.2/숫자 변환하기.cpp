#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(int x, int y, int n) {
    int answer = 0;
    set<int> num = {x};
    while(*num.begin() < y && num.find(y) == num.end()){
        set<int> tmp;
        for(const auto& a : num){
            tmp.emplace(a + n);
            tmp.emplace(a * 2);
            tmp.emplace(a * 3);
        }
        num = tmp;
        answer++;
    }    
    return num.find(y) == num.end() ? -1 : answer;
}