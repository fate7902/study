#include <iostream>
using namespace std;

// 힙을 구성하는 함수
void heapify(int* arr, int len, int i) {
	int largest = i;  // 최대값을 현재 노드로 설정
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// 왼쪽 자식 노드가 부모 노드보다 크면 largest 갱신
	if (left < len && arr[left] > arr[largest])
		largest = left;

	// 오른쪽 자식 노드가 largest보다 크면 largest 갱신
	if (right < len && arr[right] > arr[largest])
		largest = right;

	// largest가 현재 노드가 아니면 서로 위치를 교환
	if (largest != i) {
		swap(arr[i], arr[largest]);
		// 교환된 자식 노드를 기준으로 재귀적으로 heapify 호출
		heapify(arr, len, largest);
	}
}

// 힙 정렬 함수
void heapSort(int* arr, int len) {
	int n = len;

	// 최대 힙 구성
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// 힙에서 요소를 하나씩 꺼내서 정렬
	for (int i = n - 1; i >= 0; i--) {
		// 힙의 최대값(루트 노드)와 현재 노드를 교환
		swap(arr[0], arr[i]);
		// 힙 크기를 줄여서 교환된 요소를 제외하고 다시 힙을 구성
		heapify(arr, i, 0);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

	int arr[10] = { 3, 2, 5, 7, 9, 10, 1, 6, 4, 8 };
	cout << "---------------정렬 전---------------" << endl;
	for (const auto& a : arr) cout << a << " ";
	cout << endl;
	cout << "---------------정렬 후---------------" << endl;
	heapSort(arr, 10);
	for (const auto& a : arr) cout << a << " ";
}