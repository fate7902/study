#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    for(int i = 1; i < words.size(); ++i){
        if(words[i - 1].back() != words[i].front() ||
          count(words.begin(), words.begin() + i + 1, words[i]) > 1){
            return {(i + 1) % n == 0 ? n : (i + 1) % n, (i + 1) % n == 0 ? (i + 1) / n : (i + 1) / n + 1};
        }
    }
    return {0, 0};
}