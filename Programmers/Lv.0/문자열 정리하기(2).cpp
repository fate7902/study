#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string solution(string my_string) {    
    for(auto& str : my_string){
        str = tolower(str);        
    }
    sort(my_string.begin(), my_string.end());
    return my_string;
}