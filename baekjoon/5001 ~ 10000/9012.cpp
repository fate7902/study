#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    stack<int> arr;
    int k;
    cin >> k;

    while (k--) {
        string tmp;
        cin >> tmp;
        bool flag = false;
        for (int i = 0; i < tmp.size(); ++i) {
            if (tmp[i] == '(') arr.push(tmp[i]);
            else {                
                if (arr.empty()) {                    
                    flag = true;
                    break;
                }
                else arr.pop();
            }
        }
        if (arr.empty()) {
            if(flag) cout << "NO\n";
            else cout << "YES\n";
        }
        else cout << "NO\n";
        while (!arr.empty()) arr.pop();
    }
}