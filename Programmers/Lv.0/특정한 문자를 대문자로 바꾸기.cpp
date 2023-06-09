#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string my_string, string alp) {
    for_each(my_string.begin(), my_string.end(), [&](auto& c){
        if(c == alp[0]) c = toupper(c);
    });
    return my_string;
}