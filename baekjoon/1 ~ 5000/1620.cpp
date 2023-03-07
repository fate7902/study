#include <iostream>
#include <map>
#include <string>
using namespace std;

bool IsNumber(const string& str)
{
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    
    map<string, int> arrA;
    string* arrB = new string[n];    
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        arrA.emplace(str, i + 1);
        arrB[i] = str;
    }
    
    for (int i = 0; i < m; i++) {
        string str;
        cin >> str;
        if (IsNumber(str) == false) cout << arrA[str] << "\n";
        else cout << arrB[stoi(str) - 1] << "\n";
    }
    delete[] arrB;
}