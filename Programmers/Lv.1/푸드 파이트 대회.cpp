#include <string>
#include <vector>

using namespace std;

string solution(vector<int> food) {
    string answer = "0";
    for(int i = food.size() - 1; i > 0; --i){
        answer = string(food[i] / 2, to_string(i)[0]) + answer + string(food[i] / 2, to_string(i)[0]);
    }
    return answer;
}