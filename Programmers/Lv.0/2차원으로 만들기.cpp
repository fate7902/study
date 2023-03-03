#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<int> num_list, int n) {
    vector<vector<int>> answer;
    for(int i = 0; i < num_list.size(); i += n){
        vector<int> array;
        for(int j = i; j < i + n; j++){
            array.emplace_back(num_list[j]);
        }
        answer.emplace_back(array);
    }
    return answer;
}