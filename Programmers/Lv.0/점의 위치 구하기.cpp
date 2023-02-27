#include <string>
#include <vector>

using namespace std;

int solution(vector<int> dot) {
    bool type = false;
    type = dot[0] > 0 ? true : false;
        if(true == type){
            if(0 < dot[1]) return 1;
            else return 4;
        }else{
            if(0 < dot[1]) return 2;
            else return 3;
        }
}

또는

#include <string>
#include <vector>

using namespace std;

int solution(vector<int> dot) {
    return dot[0] > 0 ? ((0 < dot[1]) ? 1 : 4) : ((0 < dot[1]) ? 2 : 3);
}