#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(vector<int> elements) {
    int len = elements.size();    
    vector<int> dp(len + 1, 0); 
    dp[1] = elements[0];
    for(int i = 2; i <= len; ++i) dp[i] = dp[i - 1] + elements[i - 1];
    set<int> answer;
    for(int i = 1; i <= len; ++i) {
        for(int j = 0; j < len; ++j) {
            if (j + i <= len) answer.insert(dp[j + i] - dp[j]);
            else answer.insert(dp[len] - dp[j] + dp[i + j - len]);
        }
    }
    return answer.size();
}