#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr, vector<int> delete_list) {
    vector<int> answer;
    sort(delete_list.begin(), delete_list.end());
    copy_if(arr.begin(), arr.end(), back_inserter(answer), [&](auto& num){
        return !binary_search(delete_list.begin(), delete_list.end(), num);
    });
    return answer;
}