#include <string>
#include <vector>

using namespace std;

int solution(vector<int> num_list) {    
    return [&]{
        string odd = "";
        string even = "";
        for(const auto& v : num_list){
            if(v % 2 == 1) odd += to_string(v);
            else even += to_string(v);
        }
        return stoi(odd) + stoi(even);
    }();
}