#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int total_weight = 0, time = 0, idx = 0;
    vector<int> goal_truck;
    queue<int> bridge;
    
    while(goal_truck.size() != truck_weights.size()){
        if(bridge.size() == bridge_length){
            if(bridge.front() != 0) goal_truck.emplace_back(bridge.front());            
            total_weight -= bridge.front();
            bridge.pop();            
        }
        if(total_weight + truck_weights[idx] <= weight){
                total_weight += truck_weights[idx];
                bridge.emplace(truck_weights[idx]);
                idx++;
        }else bridge.emplace(0);
        time++;
    }
    
    return time;
}