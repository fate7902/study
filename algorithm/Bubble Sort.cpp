#include <iostream>
using namespace std;

void BubbleSort(int* arr, int size) {
	for (int i = size - 1; i >= 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main() {
	int arr[10] = { 3, 2, 5, 7, 9, 10, 1, 6, 4, 8 };
	cout << "---------------정렬 전---------------" << endl;
	for (const auto& a : arr) cout << a << " ";
	cout << endl;
	cout << "---------------정렬 후---------------" << endl;
	BubbleSort(arr, 10);
	for (const auto& a : arr) cout << a << " ";
}