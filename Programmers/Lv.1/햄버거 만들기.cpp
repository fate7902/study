#include <string>
#include <vector>

using namespace std;

int solution(vector<int> ingredient) {
    int answer = 0;
    vector<int> arr(1, 0);
    for(const auto& a : ingredient){
        if(arr.back() == 1 && a == 2) arr.back() = 12;
        else if(arr.back() == 12 && a == 3) arr.back() = 123;
        else if(arr.back() == 123 && a == 1) {
            answer++, 
            arr.pop_back();
        }
        else arr.emplace_back(a);
    }    

    return answer;
}