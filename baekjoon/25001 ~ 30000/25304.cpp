#include <iostream>

using namespace std;

int main(){
    int total_price, total_num, indi_price, indi_num;
    int sum_price = 0;
    cin >> total_price >> total_num;
    for(int i = 0; i < total_num; i++){
        cin >> indi_price >> indi_num;
        sum_price += (indi_price * indi_num);
    }
    if(total_price == sum_price) cout << "Yes";
    else cout << "No";
}