#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int solution(int N, vector<vector<int>> road, int K) {    
    vector<vector<int>> timeCost(N + 1, vector<int>(N + 1, INT_MAX));
    for (const auto &v : road) {
        timeCost[v[0]][v[1]] = timeCost[v[1]][v[0]] = min(timeCost[v[0]][v[1]], v[2]);
    }
    vector<int> minTime(N + 1, INT_MAX);
    minTime[1] = 0;
    for (int k = 0; k < N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (timeCost[i][j] != INT_MAX && minTime[i] != INT_MAX) {
                    minTime[j] = min(minTime[j], minTime[i] + timeCost[i][j]);
                }
            }
        }
    }
    int answer = 1;
    for (int i = 2; i <= N; ++i) {
        if (minTime[i] <= K) answer++;
    }
    return answer;
}