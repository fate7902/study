#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string myString) {
    for_each(myString.begin(), myString.end(), [](auto& c){
        if(c < 'l') c = 'l';
    });
    return myString;
}