#include <iostream>
using namespace std;

void SelectSort(int* arr, int size) {	
	for (int i = 0; i < size; ++i) {
		int min_index = i;
		for (int j = i + 1; j < size; ++j) {
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}			
		}
		swap(arr[min_index], arr[i]);
	}
}

int main() {
	int arr[10] = { 3, 2, 5, 7, 9, 10, 1, 6, 4, 8 };
	cout << "---------------정렬 전---------------" << endl;
	for (const auto& a : arr) cout << a << " ";
	cout << endl;
	cout << "---------------정렬 후---------------" << endl;
	SelectSort(arr, 10);
	for (const auto& a : arr) cout << a << " ";
}