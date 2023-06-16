#include <vector>
#include <set>
using namespace std;

int solution(vector<int> nums)
{
    set<int> arr(nums.begin(), nums.end());    
    return nums.size() / 2 <= arr.size() ? nums.size() / 2 : arr.size();
}