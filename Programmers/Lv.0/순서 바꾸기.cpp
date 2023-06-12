#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    reverse(num_list.begin(), num_list.begin() + n);
    reverse(num_list.begin() + n, num_list.end());
    reverse(num_list.begin(), num_list.end());
    return num_list;
}