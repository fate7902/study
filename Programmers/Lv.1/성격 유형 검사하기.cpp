#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> survey, vector<int> choices) {    
    map<char, int> m = { {'R', 0}, {'T', 0}, {'C', 0}, {'F', 0},
                         {'J', 0}, {'M', 0}, {'A', 0}, {'N', 0}};
    for(int i = 0; i < choices.size(); ++i){
        if(choices[i] > 4) m[survey[i][1]] += choices[i] - 4;
        else if(choices[i] < 4) m[survey[i][0]] += 4 - choices[i];
    }
    string answer = m['R'] >= m['T'] ? "R" : "T";
    answer += m['C'] >= m['F'] ? "C" : "F";
    answer += m['J'] >= m['M'] ? "J" : "M";
    answer += m['A'] >= m['N'] ? "A" : "N";
    return answer;
}