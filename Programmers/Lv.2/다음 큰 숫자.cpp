#include <string>
#include <vector>
#include <bitset>

using namespace std;

int solution(int n) {
    int num = bitset<32>(n).count();
    while(num != bitset<32>(++n).count());
    return n;
}