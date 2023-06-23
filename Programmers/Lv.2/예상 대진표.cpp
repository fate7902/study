#include <iostream>

using namespace std;

int solution(int n, int a, int b)
{
    int answer = 1;
    int max = a < b ? b : a;
    int min = a < b ? a : b;
    while (min + 1 != max || min % 2 != 1) {
        min = min / 2 + min % 2;
        max = max / 2 + max % 2;
        answer++;
    }
    return answer;
}