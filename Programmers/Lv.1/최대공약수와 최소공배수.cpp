#include <string>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

vector<int> solution(int n, int m) {
    vector<int> answer;
    answer.emplace_back(gcd(n , m));
    answer.emplace_back(n * m / answer[0]);
    return answer;
}