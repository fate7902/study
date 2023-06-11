#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    vector<int> answer;
    int len = num_list.size();
    int idx = 0;
    while(idx < len){
        answer.emplace_back(num_list[idx]);
        idx += n;
    }
    return answer;
}