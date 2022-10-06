#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int rFindElement(int* arr, int left, int right, int key) {
	if (left <= right) {
		int mid = (left + right) / 2;
		if (arr[mid] == key)
			return mid;
		else if (arr[mid] > key)
			return rFindElement(arr, left, mid - 1, key);
		else if (arr[mid] < key)
			return rFindElement(arr, mid + 1, right, key);
	}

	return left - 1;
}

int main() {
	int N, key;
	scanf("%d %d", &N, &key);
	int* arr = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	printf(" %d\n", rFindElement(arr, 0, N - 1, key));

	return 0;
}