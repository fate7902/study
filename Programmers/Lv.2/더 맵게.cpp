#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> q(scoville.begin(), scoville.end());
    while(q.top() < K){
        if(q.size() == 1) return -1;        
        int first = q.top(); 
        q.pop();
        int second = q.top(); 
        q.pop();
        int newScoville = first + (second * 2);
        q.emplace(newScoville);
        answer++;
    }
    return answer;
}