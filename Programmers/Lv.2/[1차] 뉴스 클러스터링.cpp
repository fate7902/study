#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string str1, string str2) {
	for_each(str1.begin(), str1.end(), [](char& c) {
		if (isalpha(c)) c = toupper(c);
		});
	for_each(str2.begin(), str2.end(), [](char& c) {
		if (isalpha(c)) c = toupper(c);
		});

	vector<string> arr1, arr2;
	for (int i = 0; i < str1.size() - 1; ++i) {
		string str = str1.substr(i, 2);
		if (isalpha(str[0]) && isalpha(str[1])) arr1.emplace_back(str);
	}
	for (int i = 0; i < str2.size() - 1; ++i) {
		string str = str2.substr(i, 2);
		if (isalpha(str[0]) && isalpha(str[1])) arr2.emplace_back(str);
	}
	sort(arr1.begin(), arr1.end());
	sort(arr2.begin(), arr2.end());

	vector<string> uni(arr1.size() + arr2.size()), inter(arr1.size() + arr2.size());
	auto iter = set_union(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), uni.begin());
	uni.erase(iter, uni.end());
	iter = set_intersection(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), inter.begin());
	inter.erase(iter, inter.end());
	int answer = (uni.size() == 0 ? 1 : static_cast<double>(inter.size()) / uni.size()) * 65536;
	return answer;
}