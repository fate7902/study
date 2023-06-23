#include <string>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

string solution(string s) {
    stringstream ss(s);
    int min = INT_MAX, max = INT_MIN;
    int tmp;
    while(ss >> tmp){
        min = min < tmp ? min : tmp;
        max = max > tmp ? max : tmp;
    }
    string answer = to_string(min) + " " + to_string(max);
    return answer;
}