#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> arr) {    
    return [&]{
        int len = arr.size();
        for(int i = 0; i < len; ++i){
            for(int j = 0; j < len; ++j){
                if(i == j) continue;
                if(arr[i][j] != arr[j][i]) return 0;
            }
        }
        return 1;
    }();
}