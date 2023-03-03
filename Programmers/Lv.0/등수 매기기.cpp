#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<vector<int>> score) {
    vector<double> average, temp;
    for (const auto& v : score) {
        double sum = 0;
        sum = (v[0] + v[1]) / 2.f;
        average.emplace_back(sum);
    }
    temp = average;
    sort(temp.begin(), temp.end(), greater<>());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    vector<int> num;

    for (int i = 0; i < temp.size(); i++) {
        int tmp = count(average.begin(), average.end(), temp[i]);
        num.emplace_back(tmp);
    }
    int* ans = new int[average.size()];
    int rank = 1;
    for (int i = 0; i < temp.size(); i++) {
        int cnt = num[i];
        for (int j = 0; j < average.size(); j++) {
            if (average[j] == temp[i]) {
                ans[j] = rank;
                cnt--;
                if (cnt == 0) {
                    rank += num[i];
                    break;
                }
            }
        }
    }

    vector<int> answer;
    for (int i = 0; i < average.size(); i++) {
        answer.emplace_back(ans[i]);
    }

    return answer;
}

// 더럽게 돌지 말고 평균이 나보다 높은애가 몇명인지 세서 표시하는 게 더 쉽고 편함