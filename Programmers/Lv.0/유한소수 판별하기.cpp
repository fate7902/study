// 방법1
#include <string>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

int solution(int a, int b) {
    b /= gcd(b, a);
    while(true){
        if(b % 2 == 0) b /= 2;
        else if(b % 5 == 0) b /= 5;
        else break;
    }
    if(b == 1) return 1;
    else return 2;    
}

// 방법2
#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    while(true){
        if(b % 2 == 0) b /= 2;
        else if(b % 5 == 0) b /= 5;
        else break;
    }
    return (a % b) ? 2 : 1;
}