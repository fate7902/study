#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    deque<int> deq(people.begin(), people.end());
    sort(deq.begin(), deq.end());
    int answer = 0;
    while(!deq.empty()){
        if(deq.size() >= 2 && deq.front() + deq.back() <= limit){
            deq.pop_front();
            deq.pop_back();
        }
        else {
            deq.pop_back();
        }
        answer++;
    }
    return answer;
}