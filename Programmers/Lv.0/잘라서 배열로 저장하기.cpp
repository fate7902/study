#include <string>
#include <vector>

using namespace std;

vector<string> solution(string my_str, int n) {
    vector<string> answer;
    int point = 0;
    while(my_str.size() > point){
        answer.emplace_back(my_str.substr(point, n));
        point += n;
    }
    return answer;
}