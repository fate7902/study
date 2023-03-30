#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int i = 0;

bool comp(const string& a, const string& b){
    return a[i] == b[i] ? b > a : b[i] > a[i];
}

vector<string> solution(vector<string> strings, int n) {
    i = n;
    sort(strings.begin(), strings.end(), comp);
    return strings;
}