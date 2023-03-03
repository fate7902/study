#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, vector<int> numlist) {
    for(int i = 0; i < numlist.size(); i++){
        if(0 != numlist[i] % n) {
            numlist.erase(numlist.begin() + i);
            i--;
        }
    }
    return numlist;
}