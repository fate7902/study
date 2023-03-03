#include <string>
#include <vector>

using namespace std;

int solution(vector<int> common) {
    int index = common.size();
    int num1 = common[2] - common[1];
    int num2 = common[1] - common[0];
    if (num1 == num2) {
        return common[index - 1] + num1;
    }
    else {
        num1 = common[2] / common[1];
        return common[index - 1] * num1;
    }
}