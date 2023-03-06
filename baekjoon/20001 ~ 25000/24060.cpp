#include <iostream>
using namespace std;

int cnt = 0;

void merge(int* arr, int start, int middle, int end, int k) {
    int* temp = new int[end + 2];
    int i = start, j = middle + 1, t = 1;
    while (i <= middle && j <= end) {
        if (arr[i] <= arr[j]) temp[t++] = arr[i++];
        else temp[t++] = arr[j++];
    }
    while (i <= middle) {
        temp[t++] = arr[i++];
    }
    while (j <= end) {
        temp[t++] = arr[j++];
    }
    i = start;
    t = 1;
    while (i <= end) {
        arr[i++] = temp[t++];
        cnt++;
        if (cnt == k) cout << temp[t - 1];
    }
    delete[] temp;
}

void merge_sort(int* arr, int start, int end, int k) {
    if (start < end) {
        int middle = (start + end) / 2;
        merge_sort(arr, start, middle, k);
        merge_sort(arr, middle + 1, end, k);
        merge(arr, start, middle, end, k);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    merge_sort(a, 0, n - 1, k);

    if (cnt < k) cout << "-1";
    delete[] a;
}