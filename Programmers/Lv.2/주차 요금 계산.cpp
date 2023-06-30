#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {
    map<int, vector<vector<string>>> m;
    for (const auto& s : records) {
        stringstream ss(s);
        string time, number, type;
        ss >> time >> number >> type;
        vector<string> tmp = { time, type };
        m[stoi(number)].emplace_back(tmp);
    }
    vector<int> answer;
    for (const auto& v : m) {
        vector<vector<string>> vec = v.second;
        int pos = 0;
        int total_time = 0;
        while (pos + 1 < vec.size()) {
            int hourA = stoi(vec[pos][0].substr(0, 2));
            int minA = stoi(vec[pos][0].substr(3, 2));
            int hourB = stoi(vec[pos + 1][0].substr(0, 2));
            int minB = stoi(vec[pos + 1][0].substr(3, 2));
            if (minB < minA) {
                minB += 60;
                hourB -= 1;
            }
            total_time += ((minB - minA) + (hourB - hourA) * 60);
            pos += 2;
        }
        if (vec.size() > pos) {
            total_time += ((59 - stoi(vec[pos][0].substr(3, 2))) + (23 - stoi(vec[pos][0].substr(0, 2))) * 60);
        }
        int fee = fees[1];
        if (total_time - fees[0] > 0) {
            total_time -= fees[0];
            fee += (((total_time / fees[2]) + (total_time % fees[2] != 0 ? 1 : 0)) * fees[3]);
        }
        answer.emplace_back(fee);
    }
    return answer;
}