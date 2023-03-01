#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int cmp = 1;
    while(true){        
        if(cmp * cmp != n){
            if(cmp * cmp < n) cmp++;
            else return 2;
        }
        else return 1;
    }
}

// cmath 헤더에 sqrt() 제곱근 구하는 함수이용 가능