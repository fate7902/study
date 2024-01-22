#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

int gainGiftEachOther[51][51] = { };

int solution(vector<string> friends, vector<string> gifts) {    
    map<int, vector<int>> gainGitfTotalNum;
    map<string, int> number;
    
    int no = 0;
    for(const auto& s : friends) {
        number[s] = no++;
        gainGitfTotalNum[number[s]] = { 0, 0, 0 };        
    }
    
    for(const auto& s : gifts){
        stringstream ss(s);
        string giver, receiver;
        ss >> giver >> receiver;
        gainGiftEachOther[number[giver]][number[receiver]]++;
        gainGitfTotalNum[number[giver]][0]++;
        gainGitfTotalNum[number[receiver]][1]++;
    }
    
    for(const auto& s : friends){
        gainGitfTotalNum[number[s]][2] = gainGitfTotalNum[number[s]][1] - gainGitfTotalNum[number[s]][0];
    }
        
    map<string, int> nextMonthGains;
    for(int i = 0; i < no; ++i){
        for(int j = i + 1; j < no; ++j){
            if((gainGiftEachOther[i][j] == 0 && gainGiftEachOther[j][i] == 0) ||
              gainGiftEachOther[i][j] == gainGiftEachOther[j][i]){
                if(gainGitfTotalNum[i][2] > gainGitfTotalNum[j][2]) nextMonthGains[friends[j]]++;
                else if(gainGitfTotalNum[i][2] < gainGitfTotalNum[j][2]) nextMonthGains[friends[i]]++;
            } else {
                if(gainGiftEachOther[i][j] > gainGiftEachOther[j][i]) nextMonthGains[friends[i]]++;
                else nextMonthGains[friends[j]]++;
            }
        }
    }
    
    int answer = 0;
    for(const auto& m : nextMonthGains){
        if(m.second > answer) answer = m.second;
    }
    
    return answer;
}