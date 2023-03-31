#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    stack<int> arr;
    while (true) {
        string tmp;
        getline(cin, tmp);        
        if (tmp == ".") break;
        bool flag = false;
        for (int i = 0; i < tmp.size(); ++i) {
            if (tmp[i] == '(' || tmp[i] == '[') arr.push(tmp[i]);
            else if(tmp[i] == ')' || tmp[i] == ']'){
                if (arr.empty()) {                    
                    flag = true;
                    break;
                }
                else {
                    if ((arr.top() == '(' && tmp[i] == ')') || (arr.top() == '[' && tmp[i] == ']')) arr.pop();
                    else break;
                }
            }
        }
        if (arr.empty()) {
            if(flag) cout << "no\n";
            else cout << "yes\n";
        }
        else cout << "no\n";
        while (!arr.empty()) arr.pop();
    }
}