#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    int A = stoi(to_string(a) + to_string(b));
    int B = 2 * a * b;
    return A > B ? A : B;
}