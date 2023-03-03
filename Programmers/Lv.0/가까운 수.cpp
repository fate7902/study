#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> array, int n) {
    vector<int> diff;
    for (int i = 0; i < array.size(); i++) {
        if (array[i] - n < 0) diff.emplace_back(-(array[i] - n));
        else diff.emplace_back(array[i] - n);
    }
    int min1 = *min_element(diff.begin(), diff.end());
    int answer = 100;
    for (int i = 0; i < diff.size(); i++) {
        if (diff[i] == min1) {
            if (array[i] < answer) {
                answer = array[i];
            }
        }
    }    
    return answer;
}