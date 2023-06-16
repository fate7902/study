#include <string>
#include <vector>

using namespace std;

int solution(int n, int m, vector<int> section) {    
    int answer = 0;
    int len = section.size();
    int cover = 0;
    for(const auto& a : section){
        if(cover < a){
            cover = a + m - 1;
            answer++;
        }
    }
    return answer;
}