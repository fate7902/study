#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    sort(lost.begin(), lost.end());
    sort(reserve.begin(), reserve.end());
    int answer = n - lost.size();
    vector<int> left;
    for (const auto& a : reserve) {
        auto tmp = find(lost.begin(), lost.end(), a);
        if (tmp != lost.end()) {
            lost.erase(tmp);
            answer++;
            continue;
        }
        left.emplace_back(a);
    }
    for (const auto& a : left) {
        auto iter = find_if(lost.begin(), lost.end(), [&](int x) {
            return abs(x - a) == 1;
        });
        if (iter != lost.end()) {
            lost.erase(iter);
            answer++;
        }
    }
    return answer;
}