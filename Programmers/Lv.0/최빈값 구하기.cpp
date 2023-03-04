#include <string>
#include <vector>

using namespace std;

int solution(vector<int> array) {
    short arr[1001] = {0, };
    for(int i = 0; i < array.size(); i++){
        arr[array[i]]++;
    }
    
    int cnt = 0, max = 0, index;
    for(int i = 0 ; i < 1001; i++){
        if(arr[i] > max){
            max = arr[i];
            cnt = 1;
            index = i;
        }else if(arr[i] == max) cnt++;
    }
    
    if(cnt != 1) return -1;
    else return index;
}