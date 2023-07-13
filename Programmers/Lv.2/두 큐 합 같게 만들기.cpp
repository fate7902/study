#include <string>
#include <vector>
#include <numeric>
using namespace std;

int solution(vector<int> queue1, vector<int> queue2) {
	long long int sum1 = accumulate(queue1.begin(), queue1.end(), 0LL);
	long long int sum2 = accumulate(queue2.begin(), queue2.end(), 0LL);
	int answer = 0, len = queue1.size(), queue1_idx = 0, queue2_idx = 0;
	while (answer <= len * 3) {
		if (sum1 > sum2) {
			sum2 += queue1[queue1_idx];
			sum1 -= queue1[queue1_idx];
			queue2.emplace_back(queue1[queue1_idx++]);
		}
		else if (sum1 < sum2) {
			sum1 += queue2[queue2_idx];
			sum2 -= queue2[queue2_idx];
			queue1.emplace_back(queue2[queue2_idx++]);
		}
		else return answer;
		answer++;
	}
	return -1;
}