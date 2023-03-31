#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n;
    m = n;

    int prev = 0, max = 0;
    vector<char> arr;
    while (n--) {
        int tmp;
        cin >> tmp;
        if (arr.empty()) {
            for (int i = 0; i < tmp; ++i)
                arr.emplace_back('+');
            arr.emplace_back('-');
            prev = max = tmp;            
        }
        else {
            if (tmp > prev) {
                for (int i = 0; i < tmp - max; ++i)
                    arr.emplace_back('+');
                max = tmp;
            }
            else {
                if (prev - tmp >= m - n) break;
            }
            arr.emplace_back('-');
            prev = tmp;
        }
    }
    if (arr.size() != m * 2 || max != m) cout << "NO\n";
    else {
        for (const auto& a : arr) {
            cout << a << "\n";
        }        
    }
}