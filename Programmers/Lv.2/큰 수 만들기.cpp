#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {    
    int num = k;
    while(num--){
        for(int i = 0; i < number.size(); ++i){
            if(number[i] < number[i + 1]){
                number.erase(number.begin() + i);
                k--;
                break;
            }
        }        
    }
    if(k > 0) number.erase(number.size() - k, k);
    return number;
}