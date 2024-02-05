#include <string>
#include <vector>

using namespace std;

int GCD(const int& a, const int& b){
    if(b == 0) return a;
    return GCD(b, a % b);
}

int ProblemGCD(const vector<int>& A, const vector<int>& B){
    int gcd = -1;
    for(const auto& i : A){
        if(gcd == -1) gcd = i;
        else gcd = GCD(gcd, i);
    }
    for(const auto& i : B){
        if(i % gcd == 0) return 0;
    }
    return gcd;
}

int solution(vector<int> arrayA, vector<int> arrayB) {
    int resultAB = ProblemGCD(arrayA, arrayB);
    int resultBA = ProblemGCD(arrayB, arrayA);
    return resultAB < resultBA ? resultBA : resultAB;
}