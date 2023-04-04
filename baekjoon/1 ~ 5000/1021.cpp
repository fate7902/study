#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    deque<int> arr;
    for (int i = 1; i <= n; ++i) arr.emplace_back(i);
    
    int cnt = 0;    
    while (m--) {
        int tmp;
        cin >> tmp;
        auto pos = find(arr.begin(), arr.end(), tmp);
        auto a = distance(arr.begin(), pos);
        auto b = distance(pos, arr.end());
        if (a <= b) {
            while (arr.front() != tmp) {
                arr.emplace_back(arr.front());
                arr.pop_front();
                cnt++;
            }            
        }
        else {
            while (arr.front() != tmp) {
                arr.emplace_front(arr.back());
                arr.pop_back();
                cnt++;
            }            
        }
        arr.pop_front();
    }
    cout << cnt;
}