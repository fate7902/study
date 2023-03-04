#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> solution(vector<int> numlist, int n) {
    sort(numlist.begin(), numlist.end(), [n](int a, int b) {
        int disA = a - n;
        int disB = b - n;
        if (abs(disA) < abs(disB)) return 1;
        else if (abs(disA) > abs(disB)) return 0;
        else {
            if (a > b) return 1;
            else return 0;
        }
        });    
    return numlist;
}