#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string myString) {
    for_each(myString.begin(), myString.end(), [](auto& c){ c = c == 'a' ? 'A' : c != 'A' ? tolower(c) : 'A';});
    return myString;
}