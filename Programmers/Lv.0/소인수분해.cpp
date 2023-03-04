#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> solution(int n) {
    bool sosu[10001] = { false, };
    sosu[0] = sosu[1] = true;
    for (int i = 2; i <= sqrt(10001); i++) {
        if (sosu[i] == true) continue;
        for (int j = i * i; j < 10001; j += i) {
            sosu[j] = true;
        }
    }

    vector<int> sosuArr;
    for (int i = 0; i < 10001; i++) {
        if (sosu[i] == true) continue;
        sosuArr.emplace_back(i);
    }

    vector<int> answer;
    int sp = 0;
    while (n != 1) {
        if (n % sosuArr[sp] == 0) {
            answer.emplace_back(sosuArr[sp]);
            n /= sosuArr[sp];
        }
        else sp++;
    }
    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());
    return answer;
}