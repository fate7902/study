#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int k, vector<int> tangerine) {
    vector<int> cnt(10000001, 0);
    for(const auto& a : tangerine) cnt[a]++;
    sort(cnt.begin(), cnt.end(), greater<int>());
    int answer = 0;
    for(const auto& a : cnt){
        k -= a;
        answer++;
        if(k <= 0) return answer;
    }    
}