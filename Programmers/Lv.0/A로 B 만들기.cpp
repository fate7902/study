#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(string before, string after) {
    for (int i = 0; i < before.size(); i++) {
        if (after.find(before[i]) == string::npos) return 0;
        else{
            int cnt = 0;
            for (int j = 0; j < before.size(); j++){
                if(before[j] == before[i]) cnt++;
                if(after[j] == before[i]) cnt--;
            }
            if(cnt != 0) return 0;            
        }
    }
    return 1;
}

// <algorithm>의 sort()로 정렬 후 같으면 1 아니면 0