#include <string>
#include <vector>

using namespace std;

string solution(vector<string> arr) {    
    return [&]{
        string answer = "";
        for(const auto& s : arr) answer += s;
        return answer;
    }();
}