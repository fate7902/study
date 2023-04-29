#include iostream
#include vector
#include stack
using namespace std;

int main() {
    ios_basesync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin  n;

    vectorint a(n);

    for (int i = 0; i  n; ++i) {
        cin  a[i];        
    }

    stackint s;
    vectorint nge(n, -1);
    for (int i = 0; i  n; ++i) {
        while (s.empty() == false && a[s.top()]  a[i]) {
            nge[s.top()] = a[i];
            s.pop();
        }
        s.emplace(i);
    }

    for (const auto& n  nge) {
        cout  n   ;
    }
}