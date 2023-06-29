#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    int len = prices.size();
    for(int i = 0; i < len - 1; ++i){
        auto iter = find_if(prices.begin() + i + 1, prices.end(), [&](int a){ return a < prices[i];});
        if(iter != prices.end()){
            answer.emplace_back(iter - prices.begin() - i);
        }
        else answer.emplace_back(len - i - 1);
    }
    answer.emplace_back(0);
    return answer;
}