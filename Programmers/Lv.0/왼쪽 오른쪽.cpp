#include <string>
#include <vector>

using namespace std;

vector<string> solution(vector<string> str_list) {    
    auto iter = str_list.begin();
    while(iter != str_list.end()){
        if(*iter == "l") return vector<string>(str_list.begin(), iter);
        else if(*iter == "r") return vector<string>(iter + 1, str_list.end());
        iter++;
    }
    return vector<string>();
}