#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

vector<int> solution(string s) {
    int erase_zero = 0;
    int trans_cnt = 0;
    while(s != "1"){
        erase_zero += count(s.begin(), s.end(), '0');
        trans_cnt++;
        s = regex_replace(s, regex("0"), "");
        int tmp = s.size();
        s = "";
        int num = 0;
        while(tmp > 0){
            if(tmp & (1 << num)) {
                s += "1";
                tmp -= (1 << num);
            }
            else s += "0";
            num++;
        }
        reverse(s.begin(), s.end());
    }
    return { trans_cnt, erase_zero };
}