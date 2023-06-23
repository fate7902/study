#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    for(int i = 1; i <= yellow; ++i){
        if(yellow % i != 0) continue;
        int tmp = yellow / i;
        int garo = (i >= tmp ? i : tmp) + 2;
        int sero = (i >= tmp ? tmp : i) + 2;
        if(2 * garo + 2 * sero - 4 == brown) return {garo, sero};
    }    
}