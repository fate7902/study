#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool cmp(const string& a, const string& b){
    if(a.size() == b.size()) return a < b;
    return a.size() < b.size();
}

bool solution(vector<string> phone_book) {    
    map<string, int> m;
    sort(phone_book.begin(), phone_book.end(), cmp);
    for(const auto& s : phone_book){
        string str = "";
        for(const auto& c : s){
            str += c;
            if(m[str] > 0) return false;
        }
        m[s] = 1;
    }
    return true;
}