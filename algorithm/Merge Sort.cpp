#include <iostream>
using namespace std;

void Merge(int* arr, int left, int mid, int right) {
	int* tmp = new int[right - left + 1]{};
	int l = left, m = mid + 1, p = 0;
    	// 왼쪽 또는 오른쪽 중 한쪽의 배열의 원소를 다 정렬 완료할때까지
	while (l <= mid && m <= right) { 
		if (arr[l] <= arr[m]) tmp[p++] = arr[l++];
		else tmp[p++] = arr[m++];
	}
    	// 남은 한쪽 배열
	if(l > mid) while (m <= right) tmp[p++] = arr[m++];
	else while (l <= mid) tmp[p++] = arr[l++];	
	// 새로 정렬된 배열을 기존의 배열에 반영
	for (int i = left, k = 0; i <= right; ++i, ++k) arr[i] = tmp[k];
	delete[] tmp;
}

void MergeSort(int* arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid); // 왼쪽 분리
		MergeSort(arr, mid + 1, right); // 오른쪽 분리
		Merge(arr, left, mid, right); // 병합
	}
}

int main() {
	int arr[10] = { 3, 2, 5, 7, 9, 10, 1, 6, 4, 8 };
	cout << "---------------정렬 전---------------" << endl;
	for (const auto& a : arr) cout << a << " ";
	cout << endl;
	cout << "---------------정렬 후---------------" << endl;
	MergeSort(arr, 0, 9);
	for (const auto& a : arr) cout << a << " ";
}