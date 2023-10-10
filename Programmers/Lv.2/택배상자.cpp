#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<int> order) {
    int answer = 0, len = order.size();
    stack<int> store;
    
    for(int i = 1; i <= len; ++i){
        store.emplace(i);
        while(!store.empty() && order[answer] == store.top()){
            answer++;
            store.pop();
        }
    }
    
    return answer;
}