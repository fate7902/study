#include <string>
#include <vector>

using namespace std;

vector<string> able{ "aya", "ye", "woo", "ma" };

int solution(vector<string> babbling) {
    int answer = 0;
    for (const auto& s : babbling) {
        int cnt[4] = { 0 };
        bool flag = true;
        for (int i = 0; i < 4; ++i) {
            int p = 0;            
            do {
                int index = s.find(able[i], p);
                if (index == string::npos) break;
                else {
                    cnt[i]++;
                    p = index + 1;                    
                }
            } while (1);
            if (cnt[i] > 1) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            int len = 0;
            for (int i = 0; i < 4; ++i) {
                len += (cnt[i] * able[i].size());
            }
            if (len == s.size()) answer++;
        }
    }

    return answer;
}