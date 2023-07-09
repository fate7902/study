#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const vector<string>& a, const vector<string>& b) {
	string tmpA = a[0];
	string tmpB = b[0];
	for_each(tmpA.begin(), tmpA.end(), [](char& c) {c = tolower(c); });
	for_each(tmpB.begin(), tmpB.end(), [](char& c) {c = tolower(c); });
	if (tmpA == tmpB) return stoi(a[1]) < stoi(b[1]);
	else return tmpA < tmpB;
}

vector<string> solution(vector<string> files) {
	vector<vector<string>> file;
	for (const auto& s : files) {
		string head = "", number = "", tail = "";
		for (int i = 0; i < s.size(); ++i) {
			if (isdigit(s[i])) {
				head = s.substr(0, i);
				for (int j = i + 1; j < s.size(); ++j) {
					if (!isdigit(s[j])) {
						int len = j - i <= 5 ? j - i : 5;
						number = s.substr(i, len);
						tail = s.substr(i + len, s.size());
						break;
					}
				}
				if (number == "") {
					number = s.substr(i, 5);
					if (i + 5 < s.size()) tail = s.substr(i + 5, s.size());
				}
				break;
			}
		}
		vector<string> vec = { head, number, tail };
		file.emplace_back(vec);
	}
	stable_sort(file.begin(), file.end(), cmp);
	vector<string> answer;
	for (const auto& v : file) {
		string str = v[0] + v[1];
		if (v[2].size() != 0) str += v[2];
		answer.emplace_back(str);
	}
	return answer;
}