#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

string solution(string polynomial) {
    vector<string> arr;
    char* ptr;
    ptr = strtok(const_cast<char*>(polynomial.c_str()), " ");
    while (ptr != NULL) {
        arr.emplace_back(ptr);
        ptr = strtok(NULL, " ");
    }

    long long numA = 0, numB = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].find("x") != string::npos) {
            if (arr[i].size() != 1) {
                string str(arr[i]);
                str.erase(remove(str.begin(), str.end(), 'x'), str.end());
                numA += stoi(str);
            }
            else numA++;
        }
        else if (arr[i].compare("+")) {
            numB += stoi(arr[i]);
        }
    }
    string answer = "";
    if (numA != 0) {
        if (numA != 1) answer += to_string(numA) + "x";
        else answer += "x";
        
    }
    if (numB != 0) {
        if (answer.size() != 0) answer += " + " + to_string(numB);
        else answer += to_string(numB);
    }
    else {
        if (numA == 0) answer += "0";
    }
    return answer;
}