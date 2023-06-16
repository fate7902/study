#include <string>
#include <vector>

using namespace std;

string solution(int a, int b) {
    vector<string> day = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    vector<int> month = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int totalday = b;
    for (int i = 0; i < a - 1; ++i) totalday += month[i];
    return day[(totalday + 4) % 7];
}