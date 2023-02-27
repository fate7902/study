#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> num_list) {
    int even = 0, odd = 0;
    for(const auto& num : num_list){
        if(0 == num % 2) even++;
        else odd++;
    }
    vector<int> answer = {even, odd};
    return answer;
}