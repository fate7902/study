#include <string>
#include <set>
using namespace std;

#define pii pair<int, int>

int solution(string dirs) {
	set<pair<pii, pii>> route;
	pii start = { 0, 0 };
	for (const auto& c : dirs) {
		switch (c) {
		case 'U':
			if (start.second + 1 <= 5) {
				pii end = { start.first, start.second + 1 };
				route.emplace(make_pair(start, end));
				route.emplace(make_pair(end, start));
				start = end;
			}
			break;
		case 'D':
			if (start.second - 1 >= -5) {
				pii end = { start.first, start.second - 1 };
				route.emplace(make_pair(start, end));
				route.emplace(make_pair(end, start));
				start = end;
			}
			break;
		case 'R':
			if (start.first + 1 <= 5) {
				pii end = { start.first + 1, start.second };
				route.emplace(make_pair(start, end));
				route.emplace(make_pair(end, start));
				start = end;
			}
			break;
		case 'L':
			if (start.first - 1 >= -5) {
				pii end = { start.first - 1, start.second };
				route.emplace(make_pair(start, end));
				route.emplace(make_pair(end, start));
				start = end;
			}
			break;
		}
	}
	return route.size() / 2;
}