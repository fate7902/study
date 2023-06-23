#include <string>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int solution(vector<int> arr) {    
    return [&]{
        int lcm = arr[0];
        for(int i = 1; i < arr.size(); ++i){
            lcm = (lcm * arr[i]) / gcd(lcm, arr[i]);
        }
        return lcm;
    }();
}