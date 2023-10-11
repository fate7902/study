#include <string>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

set<int> number;

bool CheckPrime(int number){
    if(number == 0 || number == 1) return false;
    if(number == 2) return true;
    for(int i = 2; i <= sqrt(number); ++i){
        if(number % i == 0) return false;
    }
    return true;
}

void CombineNumber(string numbers, string prev_numbers, vector<bool> used){
    for(int i = 0; i < numbers.size(); ++i){
        if(used[i] == false){
            number.emplace(stoi(prev_numbers + numbers[i]));
            used[i] = true;
            CombineNumber(numbers, prev_numbers + numbers[i], used);
            used[i] = false;
        }
    }
}

int solution(string numbers) {
    int answer = 0;
    vector<bool> used(numbers.size(), false);
    CombineNumber(numbers, "", used);
    for(const auto& i : number){
        if(CheckPrime(i)) answer++;
    }
    return answer;
}