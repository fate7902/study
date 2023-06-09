#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    vector<int> answer(num_list.begin(), num_list.end() - num_list.size() + n);
    return answer;
}