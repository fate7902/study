#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void ChangeMelody(string& m){
    string newM;
    int len = m.size();
    for(int i = len - 1; i >= 0; --i){
        if(m[i] != '#') newM += m[i];
        else newM += tolower(m[--i]);
    }
    reverse(newM.begin(), newM.end());
    m = newM;
}

string solution(string m, vector<string> musicinfos) {
    sort(musicinfos.begin(), musicinfos.end());
    ChangeMelody(m);
    string answer;
    int answerPlayTime = 0;
    
    for(const auto& s : musicinfos){
        stringstream ss(s);
        string infos[4];
        int idx = 0;
        while(getline(ss,infos[idx++],','));
        
        int playTime = stoi(infos[1].substr(3)) - stoi(infos[0].substr(3))
            + (stoi(infos[1].substr(0, 2)) - stoi(infos[0].substr(0, 2))) * 60;        
        ChangeMelody(infos[3]);
        
        string realMelody;
        if(infos[3].size() > playTime) realMelody = infos[3].substr(0, playTime);
        else{
            for(int i = 0; i < playTime / infos[3].size(); ++i) realMelody += infos[3];
            realMelody += infos[3].substr(0, playTime % infos[3].size());
        }
        
        if(realMelody.find(m) != string::npos){
            if(playTime > answerPlayTime){
                answerPlayTime = playTime;
                answer = infos[2];
            }
        }
    }
    
    return answer.size() != 0 ? answer : "(None)";
}