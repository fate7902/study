#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(int n, vector<vector<int>> wires) {
    vector<set<int>> connectedWires(n + 1, set<int>());
    for(const auto& v : wires){
        connectedWires[v[0]].emplace(v[1]);
        connectedWires[v[1]].emplace(v[0]);
    }

    int answer = n;
    for(const auto& v : wires){
        set<int> wireA, wireB;
        wireA.emplace(v[0]);
        wireB.emplace(v[1]);
        int prevSizeA, prevSizeB;

        do{
            prevSizeA = wireA.size();
            for(const auto& idx : wireA){
                for(const auto& i : connectedWires[idx]){
                    if(i != v[1]) wireA.emplace(i);
                }
            }
        }while(prevSizeA != wireA.size());

        do{
            prevSizeB = wireB.size();
            for(const auto& idx : wireB){
                for(const auto& i : connectedWires[idx]){
                    if(i != v[0]) wireB.emplace(i);
                }
            }
        }while(prevSizeB != wireB.size());

        int diff = wireA.size() - wireB.size();
        if(diff < 0) diff *= -1;
        answer = answer < diff ? answer : diff;
    }
    return answer;
}