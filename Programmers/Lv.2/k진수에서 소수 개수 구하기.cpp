#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <sstream>
#include <cmath>

using namespace std;

bool isPrime(long long int n){
    if(n == 1) return false;
    for(long long int i = 2; i <= sqrt(n); ++i){
        if(n % i == 0) return false;
    }
    return true;
}

int solution(int n, int k) {
    string str = "";
    while(n > 0) {
        str += to_string(n % k);
        n /= k;  
    }
    reverse(str.begin(), str.end());
    
    str = regex_replace(str, regex("0"), " ");
    stringstream ss(str);
    long long int num;
    int answer = 0;
    while(ss >> num) { if(isPrime(num)) answer++; }
    return answer;
}