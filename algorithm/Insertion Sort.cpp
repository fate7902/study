#include <iostream>
using namespace std;

void InsertionSort(int* arr, int size) {
	int j;
	for (int i = 1; i < size; ++i) {
		int tmp = arr[i];
		for (j = i - 1; j >= 0; --j) {
			if (arr[j] > tmp) arr[j + 1] = arr[j];
			else break;
		}
		arr[j + 1] = tmp;
	}
}

int main() {
	int arr[10] = { 3, 2, 5, 7, 9, 10, 1, 6, 4, 8 };
	cout << "---------------정렬 전---------------" << endl;
	for (const auto& a : arr) cout << a << " ";
	cout << endl;
	cout << "---------------정렬 후---------------" << endl;
	InsertionSort(arr, 10);
	for (const auto& a : arr) cout << a << " ";
}