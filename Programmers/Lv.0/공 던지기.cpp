#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers, int k) {
    return (1 + 2 * (k - 1)) % numbers.size();
}