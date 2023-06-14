#include <string>
#include <vector>

using namespace std;

int solution(vector<int> arr) {
    int answer = 0;
    vector<int> tmp(arr.begin(), arr.end());
    do{        
        for(int i = 0; i < tmp.size(); ++i){
            if(tmp[i] >= 50 && tmp[i] % 2 == 0) tmp[i] /= 2;
            else if(tmp[i] < 50 && tmp[i] % 2 == 1) tmp[i] = tmp[i] * 2 + 1;
        }
        if(arr == tmp) break;
        else{
            answer++;
            arr = tmp;
        }
    }while(true);
    return answer;
}