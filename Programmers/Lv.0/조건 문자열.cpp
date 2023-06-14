#include <string>
#include <vector>

using namespace std;

int solution(string ineq, string eq, int n, int m) {    
    return n == m ? (eq == "=" ? 1 : 0) : (ineq == "<" ? n < m : n > m);
}