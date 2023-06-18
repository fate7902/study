#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    int rank[7] = { 6, 6, 5, 4, 3, 2, 1 };
    int zero = 0;
    int match = 0;
    for(int i = 0; i < 6; ++i){
        if(lottos[i] == 0) zero++;
        else if(find(win_nums.begin(), win_nums.end(), lottos[i]) != win_nums.end()) match++;
    }
    return { rank[match + zero], rank[match] };
}