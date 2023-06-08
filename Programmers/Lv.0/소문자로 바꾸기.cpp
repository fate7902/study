#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string myString) {    
    for_each(myString.begin(), myString.end(), [](auto& c){c = tolower(c);});
    return myString;
}