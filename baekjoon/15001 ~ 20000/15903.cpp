#include <iostream>
#include <queue>
#include <numeric>
using namespace std;

struct cmp {
    bool operator()(const long long int a, const long long int b) {
        return a > b;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    priority_queue<long long int, vector<long long int>, cmp> q;
    while (n--) {
        int tmp;
        cin >> tmp;
        q.emplace(tmp);        
    }

    for (int i = 0; i < m; ++i) {
        long long int tmp = q.top();
        q.pop();
        tmp += q.top();
        q.pop();
        q.emplace(tmp);
        q.emplace(tmp);
    }

    long long int sum = 0;
    while (!q.empty()) {
        sum += q.top();
        q.pop();
    }
    cout << sum;
}