#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> lines) {
    short num[200] = { 0 };
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (lines[i][1] <= lines[j][0] || lines[i][0] >= lines[j][1]) continue;
            vector<int> tmp{ lines[i][0], lines[i][1], lines[j][0],lines[j][1] };
            sort(tmp.begin(), tmp.end());            
            for (int k = tmp[1]; k < tmp[2]; ++k) {
                num[k + 100]++;
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < 200; ++i) {
        if (num[i] == 0) continue;
        answer++;
    }

    return answer;
}