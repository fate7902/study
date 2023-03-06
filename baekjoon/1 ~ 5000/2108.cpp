#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;

vector<int> arr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
	int case_num, num;
	int numbers[8001] = { 0, };
	cin >> case_num;
	for (int i = 0; i < case_num; i++) {
		cin >> num;
		arr.emplace_back(num);
		numbers[num + 4000]++;
	}
	sort(arr.begin(), arr.end());

	int median = round(accumulate(arr.begin(), arr.end(), 0.0) / (double)arr.size());
	cout << median << "\n";
	cout << arr[arr.size() / 2] << "\n";

	int most = 0, most_index;
	bool check = false;
	for (int i = 0; i < 8001; i++)
	{
		if (numbers[i] == 0) continue;			
		if (numbers[i] == most) {
			if (check == true) {
				most_index = i - 4000;
				check = false;
			}
		}
		else if (numbers[i] > most)	{
			most_index = i - 4000;
			most = numbers[i];
			check = true;
		}
	}
	cout << most_index << "\n";
	cout << *max_element(arr.begin(), arr.end()) - *min_element(arr.begin(), arr.end());
}