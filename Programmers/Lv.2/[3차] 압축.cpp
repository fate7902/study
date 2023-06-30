#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(string msg) {
    map<string, int> index;
	for (char i = 'A'; i <= 'Z'; ++i) {
		index[string(1, i)] = i - 'A' + 1;
	}
    vector<int> answer;
    for(int i = 0; i < msg.size(); ++i){
        int pos = i;
        string now(1, msg[pos]);
        while(index.find(now) != index.end()){
            if(i < msg.size() - 1) now += msg[++pos];
            else break;
        }
        if (i != pos) {
			i = pos - 1;
			index[now] = index.size() + 1;
			answer.emplace_back(index[now.substr(0, now.size() - 1)]);
		}
		else answer.emplace_back(index[now]);
    }    
    return answer;
}