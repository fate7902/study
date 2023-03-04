#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> solution(vector<int> emergency) {
    vector<int> array;
    array = emergency;
    sort(array.begin(), array.end(), greater<>());
    vector<int> answer;
    for (int i = 0; i < array.size(); i++) {
        int index = find(array.begin(), array.end(), emergency[i]) - array.begin();
        answer.emplace_back(index + 1);
    }
    return answer;
}