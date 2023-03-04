#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int denum1, int num1, int denum2, int num2) {
    int a = denum1 * num2 + denum2 * num1;
    int b = num1 * num2;
    int temp = min(a, b);
    for (int i = 2; i <= temp; i++) {
        if (a % i == 0 && b % i == 0) {
            a /= i;
            b /= i;
            temp /= i;
            i = 1;
        }
    }

    vector<int> answer = { a, b };
    return answer;
}