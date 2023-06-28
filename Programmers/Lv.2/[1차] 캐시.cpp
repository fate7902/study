#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    deque<string> deq;
    for(auto& s : cities){
        for_each(s.begin(), s.end(), [](auto& c){c = tolower(c);});
        auto iter = find(deq.begin(), deq.end(), s);
        if(iter == deq.end()) {
            answer += 5;
            if(deq.size() == cacheSize && !deq.empty()) deq.erase(deq.begin());
            if(deq.size() < cacheSize) deq.emplace_back(s);
        }
        else {
            answer++; 
            deq.erase(iter);
            deq.emplace_back(s);
        }
    }
    return answer;
}