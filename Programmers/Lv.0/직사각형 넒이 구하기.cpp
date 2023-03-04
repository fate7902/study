#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> dots) {
    vector<int> x, y;
    for(const auto& v : dots){
        x.emplace_back(v[0]);
        y.emplace_back(v[1]);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end()); 
    return (x[1] - x[0]) * (y[1] - y[0]);
}