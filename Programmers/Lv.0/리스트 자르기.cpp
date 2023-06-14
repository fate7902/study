#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, vector<int> slicer, vector<int> num_list) {    
    switch(n){
        case 1:
            return vector<int>(num_list.begin(), num_list.begin() + slicer[1] + 1);            
        case 2:
            return vector<int>(num_list.begin() + slicer[0], num_list.end());            
        case 3:
            return vector<int>(num_list.begin() + slicer[0], num_list.begin() + slicer[1] + 1);            
        case 4:
            return [&]{
                vector<int> answer;
                for(int i = slicer[0]; i <= slicer[1]; i += slicer[2]){
                    answer.emplace_back(num_list[i]);
                }
                return answer;
            }();
    }    
}