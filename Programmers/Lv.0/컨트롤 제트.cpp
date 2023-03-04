#include <string>
#include <vector>
#include <cstring>

using namespace std;

int solution(string s) {
    vector<string> arr;
    char* ptr = strtok(const_cast<char*>(s.c_str()), " ");
    while (ptr != NULL) {
        arr.emplace_back(ptr);
        ptr = strtok(NULL, " ");
    }

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].compare("Z") == 0) {
            if (i - 1 >= 0) {
                arr.erase(arr.begin() + (i - 1), arr.begin() + (i + 1));
                i -= 2;
            }else{
                arr.erase(arr.begin() + (i - 1), arr.begin() + i);
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < arr.size(); i++) {
        answer += stoi(arr[i]);
    }
   
    return answer;
}