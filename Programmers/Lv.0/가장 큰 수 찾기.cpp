#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array) {
    vector<int> answer;
    answer.emplace_back(*max_element(array.begin(), array.end()));
    answer.emplace_back(max_element(array.begin(), array.end()) - array.begin());
    return answer;
}

// max_element()를 따로 변수에 저장후 distance() 함수를 이용해 인덱스를 구할 수도 있음.