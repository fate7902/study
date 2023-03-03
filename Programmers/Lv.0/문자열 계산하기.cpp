#include <string>
#include <vector>
#include <cstring>

using namespace std;

int solution(string my_string) {
    vector<string> arr;
    char* ptr = strtok(const_cast<char*>(my_string.c_str()), " ");
    while (ptr != NULL) {
        arr.emplace_back(ptr);
        ptr = strtok(NULL, " ");
    }
    int answer = stoi(arr[0]);
    for (int i = 1; i < arr.size(); i += 2) {
        if (arr[i] == "+") {
            answer += stoi(arr[i + 1]);
        }
        else {
            answer -= stoi(arr[i + 1]);
        }
    }
    return answer;
}

// <sstream>헤더의 stringstream으로도 가능