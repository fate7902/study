#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

bool Judge(float a, float b){
    if(b / a == 1.f || b / a == 2.f || b / a == 3 / 2.f || b / a == 4 / 3.f) return true;
    else return false;
}

long long SameWeightNumber(long long a){
    if(a > 1) return SameWeightNumber(a - 1) + a;
    return a;
}

long long solution(vector<int> weights) {
    set<int> oneWeights;
    map<int, int> weightNum;
    for(const auto& i : weights){
        oneWeights.emplace(i);
        weightNum[i]++;
    }

    long long answer = 0;
    for(const auto& m : weightNum) answer += SameWeightNumber(m.second - 1);

    for(auto iterA = oneWeights.begin(); iterA != --oneWeights.end(); ++iterA){        
        auto tempIter = iterA;
        tempIter++;
        for(auto iterB = tempIter; iterB != oneWeights.end(); iterB++){
            if(*iterB / (float)*iterA > 2.f) break;
            if(Judge(*iterA, *iterB)) answer += (weightNum[*iterA] * weightNum[*iterB]);
        }
    }
    return answer;
}