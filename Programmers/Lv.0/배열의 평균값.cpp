#include <string>
#include <vector>

using namespace std;

double solution(vector<int> numbers) {
    double answer = 0;    
    for(const auto& v : numbers)
        answer += v;
    return answer / numbers.size();
}

또는 

#include <string>
#include <vector>
#include <numeric>
using namespace std;

double solution(vector<int> numbers) {
    double answer = accumulate(numbers.begin(),numbers.end(),0.0) / numbers.size();
    return answer;
}