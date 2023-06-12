#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string myString, string pat) {
    for_each(myString.begin(), myString.end(), [](auto& c){ c = tolower(c);});
    for_each(pat.begin(), pat.end(), [](auto& c){ c = tolower(c);});    
    return myString.find(pat) == string::npos ? 0 : 1;
}