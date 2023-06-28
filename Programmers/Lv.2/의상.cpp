#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {    
    map<string, int> m;
    for(const auto& v : clothes) m[v[1]]++;
    int answer = 1;
    for(const auto& e : m){
        answer *= (e.second + 1);
    }
    return answer - 1;
}