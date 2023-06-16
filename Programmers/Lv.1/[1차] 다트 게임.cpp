#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(string dartResult) {
    vector<int> point(4, 0);
    int now = 1;
    for(int i = 0; i < dartResult.size(); ++i){
        if(isdigit(dartResult[i])){
            string tmp = string(1, dartResult[i]);
            if(isdigit(dartResult[i + 1])){
                tmp += dartResult[i + 1];
                i++;
            }
            point[now] = stoi(tmp);
        }
        else if(isalpha(dartResult[i])){
            switch(dartResult[i]){
                case 'S': point[now] = pow(point[now], 1); break;
                case 'D': point[now] = pow(point[now], 2); break;
                case 'T': point[now] = pow(point[now], 3); break;
            }
            if(i + 1 < dartResult.size() && isdigit(dartResult[i + 1])) {
                now++;
            }
        }
        else{
            switch(dartResult[i]){
                case '*':
                    point[now] *= 2;
                    if(now > 1) point[now - 1] *= 2;
                    break;
                case '#':
                    point[now] *= -1;
                    break;
            }
            now++;
        }
    }
    int answer = 0;
    for(const auto& p : point) answer += p;
    return answer;
}