#include <string>
#include <vector>

using namespace std;

int solution(int price) {
    if(price >= 500000){
        price *= 0.8f; 
    }
    else if(price >= 300000){
         price *= 0.9f;    
    }
    else if(price >= 100000){
        price *= 0.95f;
    }
    return price;
}