#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    queue<int> arr;
    for (int i = 1; i <= n; ++i) arr.emplace(i);

    cout << "<";
    while (arr.size() > 1) {
        for (int i = 1; i < k; ++i) {
            int tmp = arr.front();
            arr.pop();
            arr.emplace(tmp);
        }
        cout << arr.front() << ", ";
        arr.pop();
    }

    cout << arr.front() << ">";
}