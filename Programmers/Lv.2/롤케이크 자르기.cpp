#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<int> topping) {
    int answer = 0;
    int len = topping.size();
    unordered_map<int, int> A, B;
    for(const auto& a : topping) B[a]++;
    for(int i = 0; i < len; ++i){
        A[topping[i]]++;
        B[topping[i]]--;
        if(B[topping[i]] == 0) B.erase(topping[i]);        
        if(A.size() == B.size()) answer++;
        else if(A.size() > B.size()) break;
    }
    return answer;
}