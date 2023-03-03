#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string A, string B) {
    int answer = 0;
    bool same = false;
    if(A.compare(B) != 0){
        for(int i = 1; i < A.size(); i++){
            answer++;
            rotate(A.rbegin(), A.rbegin() + 1, A.rend());
            if(A.compare(B) == 0){
                same = true;
                break;
            }
        }
        if(same == true) return answer;
        else return -1;
    }
    return 0;
}

// 한쪽으로 민다는 것은 같은 것을 2개를 이어붙이면 원본이 생기는 것을 말하므로
// find()로 간단하게 해결 가능하다.
//int solution(string A, string B)
//{
//    B += B;
//    return B.find(A);
//}