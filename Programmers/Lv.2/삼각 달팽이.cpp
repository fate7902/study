#include <string>
#include <vector>

using namespace std;

int triangle[1001][1001];
int num = 1;

void FillNumber(int x, int y, int n){
    if(n <= 0) return;
    
    for(int i = 0; i < n; ++i) triangle[x + i][y] = num++;
    for(int i = 1; i <= n - 1; ++i) triangle[x + n - 1][y + i] = num++;
    for(int i = n - 2, j = 1; i > 0; --i, ++j) triangle[x + n - 1 - j][y + i] = num++;
    FillNumber(x + 2, y + 1, n - 3);
}

vector<int> solution(int n) {
    FillNumber(1, 1, n);
    
    vector<int> answer;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= i; ++j) answer.emplace_back(triangle[i][j]);
    }
    return answer;
}