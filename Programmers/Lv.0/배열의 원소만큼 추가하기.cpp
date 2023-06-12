#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer;
    for(const auto& a : arr){
        answer.insert(answer.end(), a, a);
    }
    return answer;
}