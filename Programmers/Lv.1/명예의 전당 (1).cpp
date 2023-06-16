#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(int k, vector<int> score) {
    vector<int> answer;
    multiset<int> s;
    for (const auto& a : score) {
        s.emplace(a);
        if (s.size() < k) answer.emplace_back(*s.begin());
        else {
            auto it = s.rbegin();
            advance(it, k - 1);
            answer.emplace_back(*it);
        }
    }
    return answer;
}