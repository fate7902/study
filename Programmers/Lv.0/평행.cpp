#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> dots) {
    int answer = 0;
    for (int i = 0; i < dots.size() - 1; i++) {
        for (int j = i + 1; j < dots.size(); j++) {
            vector<vector<int>> a, b;
            for (int k = 0; k < dots.size(); k++) {
                if (k == i || k == j) a.emplace_back(dots[k]);
                else b.emplace_back(dots[k]);
            }
            float lineA = (float)(a[1][1] - a[0][1]) / (a[1][0] - a[0][0]);
            float lineB = (float)(b[1][1] - b[0][1]) / (b[1][0] - b[0][0]);
            if (lineA == lineB) answer++;
        }
    }
    if (answer > 0) return 1;
    else return 0;
}