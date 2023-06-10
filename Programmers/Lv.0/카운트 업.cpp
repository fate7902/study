#include <string>
#include <vector>

using namespace std;

vector<int> solution(int start, int end) {
    vector<int> answer(end - start + 1);
    for(auto& v : answer){
        v = start++;
    }
    return answer;
}