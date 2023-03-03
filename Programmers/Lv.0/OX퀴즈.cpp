#include <string>
#include <cstring>
#include <vector>

using namespace std;

vector<string> solution(vector<string> quiz) {
    vector<string> answer, temp;
    for (int i = 0; i < quiz.size(); i++) {
        temp.clear();
        const char* ptr;
        ptr = strtok(const_cast<char*>(quiz[i].c_str()), " ");
        while (ptr != NULL) {
            temp.emplace_back(ptr);
            ptr = strtok(NULL, " ");
        }
        int num = 0;
        for (int j = 0; j < temp.size(); j++) {
            if (j == 0) num = stoi(temp[j]);
            else {
                if (temp[j].compare("+") == 0) num += stoi(temp[j++ + 1]);
                else if (temp[j].compare("-") == 0) num -= stoi(temp[j++ + 1]);
                else {
                    if (num == stoi(temp[j++ + 1])) answer.emplace_back("O");
                    else answer.emplace_back("X");
                }
            }
        }
    }
    return answer;
}