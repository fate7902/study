#include <string>
#include <vector>

using namespace std;

int solution(vector<int> array) {
    vector<string> str;
    for(int i = 0; i < array.size(); i++){
        str.emplace_back(to_string(array[i]));
    }
    int answer = 0;
    for(int i = 0; i < str.size(); i++){
        for(int j = 0; j < str[i].size(); j++){
            if(str[i][j] == '7') answer++;
        }
    }
    return answer;
}