#include <iostream>
using namespace std;

void QuickSort(int* arr, int left, int right) {
	if (left >= right) return;

	int pivot = left;
	int start = pivot + 1;
	int end = right;
	while (start <= end) {
		while (start <= end && arr[start] <= arr[pivot]) start++;
		while (end >= start && arr[end] >= arr[pivot]) end--;

		if (start > end) swap(arr[end], arr[pivot]);
		else swap(arr[start], arr[end]);
	}

	QuickSort(arr, left, end - 1);
	QuickSort(arr, end + 1, right);
}

int main() {
	int arr[10] = { 3, 2, 5, 7, 9, 10, 1, 6, 4, 8 };
	cout << "---------------정렬 전---------------" << endl;
	for (const auto& a : arr) cout << a << " ";
	cout << endl;
	cout << "---------------정렬 후---------------" << endl;
	QuickSort(arr, 0, 9);
	for (const auto& a : arr) cout << a << " ";
}