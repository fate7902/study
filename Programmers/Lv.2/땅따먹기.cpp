#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> land){
    int len = land.size();
    for(int i = 0; i < len - 1; ++i){
        land[i + 1][0] += max(land[i][1], max(land[i][2], land[i][3]));
        land[i + 1][1] += max(land[i][0], max(land[i][2], land[i][3]));
        land[i + 1][2] += max(land[i][0], max(land[i][1], land[i][3]));
        land[i + 1][3] += max(land[i][0], max(land[i][1], land[i][2]));
    }
    return *max_element(land[len - 1].begin(), land[len - 1].end());
}