#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string myString, string pat) {
    for_each(myString.begin(), myString.end(), [](auto& c){ c = c == 'A' ? 'B' : 'A';});    
    return myString.find(pat) == string::npos ? 0 : 1;
}