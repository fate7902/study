#include <iostream>
#include <vector>
using namespace std;

int main() {
    int case_num, tmp;
    cin >> case_num;
    vector<int> array;
    for(int i = 0; i < case_num; i++){
        cin >> tmp;
        array.emplace_back(tmp);
    }
    int answer = 0;
    for(int i = 0; i <array.size(); i++){
        if(array[i] > 1){
            int divisor_cnt = 0;
            for(int j = 1; j <= array[i]; j++){
                if(array[i] % j == 0) {
                    if(divisor_cnt < 2) divisor_cnt++;
                    else {
                        divisor_cnt++; 
                        break;
                    }
                }
            }
            if(divisor_cnt == 2) answer++;
        }
    }
    cout << answer;
}