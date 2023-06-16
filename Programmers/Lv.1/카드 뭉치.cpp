#include <string>
#include <vector>

using namespace std;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    string answer = "Yes";
    for(const auto& s : goal){
        if(cards1[0] == s) cards1.erase(cards1.begin());
        else if(cards2[0] == s) cards2.erase(cards2.begin());
        else {
            answer = "No";
            break;
        }
    }
    return answer;
}