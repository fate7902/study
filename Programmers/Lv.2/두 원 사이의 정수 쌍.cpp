#include <string>
#include <vector>
#include <cmath>

using namespace std;

long long solution(int r1, int r2) {
    long long answer = 0;
    long long minR = static_cast<long long>(r1) * r1;
    long long maxR = static_cast<long long>(r2) * r2;
    for(long long x = 1; x <= r2; ++x){        
        long long minY = sqrt(minR - (x * x));
        if((x * x) + (minY * minY) < minR) minY++;
        long long maxY = sqrt(maxR - (x * x));
        answer += (maxY - minY + 1);
    }
    return answer * 4;
}