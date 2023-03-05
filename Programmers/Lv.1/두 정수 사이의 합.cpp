#include <string>
#include <vector>

using namespace std;

long long solution(int a, int b) {
    int small = a > b ? b : a;
    int big = a > b ? a : b;
    double mid = (big + small) / 2.f;
    long long answer = mid * (big - small + 1);    
    return answer;
}