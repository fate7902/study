#include <string>
#include <vector>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    for(int i = 0; i < arr1.size(); ++i){
        string str;
        int k = n - 1;
        while(k >= 0){
            if((arr1[i] & (1 << k)) || (arr2[i] & (1 << k))) str += "#";
            else str += " ";
            k--;
        }
        answer.emplace_back(str);
    }
    return answer;
}