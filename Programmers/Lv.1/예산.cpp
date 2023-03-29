#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> d, int budget) {
    sort(d.begin(), d.end());
    int answer = 0;
    int sum = 0;
    for(const auto n : d){
        sum += n;
        if(sum > budget) break;
        answer++;
    }
    return answer;
}