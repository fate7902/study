#include <string>
#include <vector>

using namespace std;

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) {
    int answer = 0;
    int hp = health, time = attacks.back()[0];
    int attack_no = 0, duration = 0;
    
    for(int i = 1; i <= time; ++i){
        if(attacks[attack_no][0] == i){            
            hp -= attacks[attack_no][1];
            if(hp <= 0) break;
            duration = 0;
            attack_no++;
        } else {
            duration++;
            hp = hp + bandage[1] <= health ? hp + bandage[1] : health;
            if(duration == bandage[0]){
                duration = 0;
                hp = hp + bandage[2] <= health ? hp + bandage[2] : health;
            }
        }
    }
    return hp <= 0 ? -1 : hp;
}