#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b){
    if(a[1] - a[0] == b[1] - b[0]) return a[0] < b[0];
    return a[1] - a[0] < b[1] - b[0];
}

vector<int> solution(vector<int> sequence, int k) {
    int len = sequence.size();
    vector<int> dp(len + 1, 0);
    dp[0] = 0;
    for(int i = 0; i < len; ++i) dp[i + 1] = dp[i] + sequence[i];
    vector<vector<int>> ret;
    int s = 0, e = 0;
    while(e <= len){        
        if(dp[e] - dp[s] == k){
            vector<int> tmp = {s, e - 1};
            ret.emplace_back(tmp);
            s++;
        }
        else if(dp[e] - dp[s] > k) s++;
        else e++;
    }
    sort(ret.begin(), ret.end(), cmp);
    return ret.front();
}