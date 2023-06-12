#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {    
    return [&]{
        int A = stoi(to_string(a) + to_string(b));
        int B = stoi(to_string(b) + to_string(a));
        return A > B ? A : B;
    }();
}