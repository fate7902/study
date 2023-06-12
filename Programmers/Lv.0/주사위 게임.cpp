#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int a, int b) {    
    return a % 2 == 0 ? (b % 2 == 0 ? abs(a - b) : (a + b) * 2) : (b % 2 == 0 ? (a + b) * 2 : a * a + b * b);
}