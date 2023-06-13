#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <sstream>

using namespace std;

vector<string> solution(string myString) {
    vector<string> answer;
    myString = regex_replace(myString, regex("x"), " ");
    stringstream ss(myString);
    string str;
    while(ss >> str){
        answer.emplace_back(str);
    }
    sort(answer.begin(), answer.end());
    return answer;
}