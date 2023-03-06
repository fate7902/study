#include <iostream>
using namespace std;

int main() {
    int row, col;
    cin >> row >> col;
    int** arrayA = new int*[row];
    int** arrayB = new int*[row];
    
    for(int i = 0; i < row; i++){
        arrayA[i] = new int[col];
        arrayB[i] = new int[col];
    }    
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cin >> arrayA[i][j];
        }
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cin >> arrayB[i][j];
        }
    }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << arrayA[i][j] + arrayB[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < row; i++){
	    delete[] arrayA[i];
        delete[] arrayB[i];
    }
    delete[] arrayA;
    delete[] arrayB;
}