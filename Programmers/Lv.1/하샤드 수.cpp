#include <string>
#include <vector>

using namespace std;

bool solution(int x) {
    int num = 0, tmp = x;
    while(tmp > 0){
        num += tmp % 10;
        tmp /= 10;
    }    
    
    return x % num == 0 ? true : false;
}