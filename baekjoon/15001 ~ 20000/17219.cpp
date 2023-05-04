#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    map<string, string> note;
    while (n--) {
        string site, pw;
        cin >> site >> pw;
        note[site] = pw;
    }

    while (m--) {
        string site;
        cin >> site;
        cout << note[site] << "\n";
    }
}