#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

map<string, string> m = { {"zero", "0"}, {"one", "1"}, {"two", "2"},
                       {"three", "3"}, {"four", "4"}, {"five", "5"},
                       {"six", "6"}, {"seven", "7"}, {"eight", "8"},
                       {"nine", "9"}};
int solution(string s) {
    for(const auto& t : m){
        s = regex_replace(s, regex(t.first), t.second);
    }
    return stoi(s);
}