#include <string>
#include <vector>
#include <cmath>

using namespace std;

//b C s = b!/(s! * (b - s)!)
double factorial(int n){    
    if(n > 1) return factorial(n - 1) * n;
    else return 1;
}

int solution(int balls, int share) {
    double ret = factorial(balls) / (factorial(share) * factorial(balls - share));
    return round(ret);
}

// combination 이라는 방식도 있음