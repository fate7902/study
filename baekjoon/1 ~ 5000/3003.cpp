#include <iostream>
#include <vector>
using namespace std;

int main() {
    int check[6] = {1,1,2,2,2,8};
    int array[6];
    for(int i=0; i<6; i++)
        cin >> array[i];
    for(int i=0; i<6; i++){
        cout << check[i] - array[i] << " ";
    }   
}