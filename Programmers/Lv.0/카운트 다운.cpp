#include <string>
#include <vector>

using namespace std;

vector<int> solution(int start, int end) {
    int len = start - end + 1;
    vector<int> answer(len);
    for(int i = 0; i < len; ++i){
        answer[i] = start--;
    }
    return answer;
}