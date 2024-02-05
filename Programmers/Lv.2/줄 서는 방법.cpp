#include <string>
#include <vector>
#include <cmath>

using namespace std;

int GetNumber(vector<int>& remainNumbers, long long& k){
    double caseNum = 1;
    for(int i = 1; i < remainNumbers.size(); ++i) caseNum *= i;
    int currentIndex = ceil(k / caseNum) - 1;
    int result = remainNumbers[currentIndex];
    remainNumbers.erase(remainNumbers.begin() + currentIndex);
    k -= (currentIndex * caseNum);
    return result;
}

vector<int> solution(int n, long long k) {
    vector<int> remainNumbers, answer;
    for(int i = 1; i <= n; ++i) remainNumbers.emplace_back(i);
    for(int i = 1; i <= n; ++i) answer.emplace_back(GetNumber(remainNumbers, k));    
    return answer;
}