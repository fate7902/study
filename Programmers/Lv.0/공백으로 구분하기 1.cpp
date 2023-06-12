#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> solution(string my_string) {
    vector<string> answer;
    stringstream str(my_string);
    string tmp;
    while(str >> tmp){
        answer.emplace_back(tmp);
    }
    return answer;
}