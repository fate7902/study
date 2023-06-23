#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0; 
    for (int i = 1; i <= n; ++i) {
        int start = n / i - (i - 1) / 2, end = start + i - 1;
        if (start > 0 && (start + end) * i / 2 == n) {
            answer++;
        }
    }
    return answer;
}