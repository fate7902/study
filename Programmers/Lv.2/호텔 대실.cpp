#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<string>> book_time) {
    sort(book_time.begin(), book_time.end());
    vector<vector<string>> room;
    for(const auto& b : book_time){
        string start = b[0], end = b[1];
        if(room.empty()) {
            room.emplace_back(vector<string>{start, end});
            continue;
        }
        bool flag = false;
        for(auto& r : room){
            if((r[0] <= start && start <= r[1]) || (r[0] <= end && end <= r[1])) continue;            
            if(r[1] < start){
                int h1 = stoi(r[1].substr(0, 2)), m1 = stoi(r[1].substr(3));
                int h2 = stoi(start.substr(0, 2)), m2 = stoi(start.substr(3));
                int timeDiff = (h2 - h1) * 60 + (m2 - m1);
                if(timeDiff >= 10) {
                    flag = true;
                    r[1] = end;
                    break;
                }
            }else{
                int h1 = stoi(r[0].substr(0, 2)), m1 = stoi(r[0].substr(3));
                int h2 = stoi(end.substr(0, 2)), m2 = stoi(end.substr(3));
                int timeDiff = (h1 - h2) * 60 + (m1 - m2);
                if(timeDiff >= 10) {
                    flag = true;
                    r[0] = start;
                    break;
                }
            }
        }
        if(flag == false) room.emplace_back(vector<string>{start, end});
    }
    return room.size();
}