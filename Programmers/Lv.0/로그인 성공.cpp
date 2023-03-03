#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> id_pw, vector<vector<string>> db) {
    vector<string> id, pw;
    for (const auto& v : db) {
        id.emplace_back(v[0]);
        pw.emplace_back(v[1]);
    }

    auto check_id = find(id.begin(), id.end(), id_pw[0]);    
    if (check_id == id.end()) return "fail";
    int index = check_id - id.begin();
    if (pw[index].compare(id_pw[1]) != 0) return "wrong pw";
    return "login";
}