#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int big_top = 0, small_top = 0;
    for(int i = 0; i < sizes.size(); ++i){
        big_top = max(big_top, max(sizes[i][0], sizes[i][1]));
        small_top = max(small_top, min(sizes[i][0], sizes[i][1]));
    }
    return big_top * small_top;
}