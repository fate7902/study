#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> solution(vector<string> strArr) {
    return [&]{
        for(int i = 0; i < strArr.size(); ++i){
            if(i % 2 == 0) for_each(strArr[i].begin(), strArr[i].end(), [](auto& c){c = tolower(c);});
            else for_each(strArr[i].begin(), strArr[i].end(), [](auto& c){c = toupper(c);});
        }
        return strArr;
    }();
}