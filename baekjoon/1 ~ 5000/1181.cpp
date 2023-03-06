#include <iostream>
#include <set>
using namespace std;

struct cmp {
    bool operator() (const string& a, const string& b) const {
        if (a.size() == b.size()) return a < b;
        return a.size() < b.size();
    }
};

set<string, cmp> arr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int case_num;
    string str;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> str;
        arr.insert(str);
    }

    for (const auto& s : arr) {
        cout << s << "\n";
    }
}