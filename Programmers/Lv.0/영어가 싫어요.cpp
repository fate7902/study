#include <string>
#include <vector>

using namespace std;

vector<string> number = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

long long solution(string numbers) {
    int start = 0, len = 3;
    vector<int> arr;
    while (true) {
        bool find = false;
        for (int i = 0; i < number.size(); i++) {
            if (numbers.substr(start, len).compare(number[i]) == 0) {
                arr.emplace_back(i);
                start += len;
                len = 3;
                find = true;
                break;
            }
        }
        if (find == false) len++;
        if (start == numbers.size()) break;
    }

    string str;
    for (int i = 0; i < arr.size(); i++) {
        str += to_string(arr[i]);
    }

    long long answer = stoll(str);
    return answer;
}

// 변수 범위를 항상 고려하자