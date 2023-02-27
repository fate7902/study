#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    for(const int& num : numbers){
        answer.emplace_back(num * 2);
    }
    return answer;
}