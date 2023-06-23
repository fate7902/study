#include <string>
#include <vector>

using namespace std;
constexpr int MOD = 1234567;
int dp[100001]{};

int fibo(int n){
    if(n <= 1) return dp[n];
    else {
        if(dp[n] == 0) dp[n] = (fibo(n - 1) % MOD + fibo(n - 2) % MOD) % MOD;
        return dp[n];
    }
}

int solution(int n) {
    dp[0] = 0; dp[1] = 1;
    return fibo(n);
}