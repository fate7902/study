#include <string>
#include <vector>

using namespace std;

int solution(int num) {
    if (num == 1) return 0;
    else {
        int answer = 0;
        long long tmp = num;
        while (answer <= 500 && tmp != 1) {
            tmp = tmp % 2 == 0 ? tmp / 2 : tmp * 3 + 1;
            answer++;
        }
        return answer > 500 ? -1 : answer;
    }
}