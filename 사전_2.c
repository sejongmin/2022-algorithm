#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int iFindElement(int* arr, int N, int key) {
	int left = 0;
	int right = N - 1;
	int mid;

	if (arr[right] < key)
		return N;

	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == key)
			return mid;
		else if (arr[mid] > key) {
			right = mid - 1;
			continue;
		}
		else {
			left = mid + 1;
			continue;
		}
	}
	if (arr[right] > key && right >= 0)
		return right;
	else
		return left;
}

int main() {
	int N, key;
	scanf("%d %d", &N, &key);
	int* arr = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	printf(" %d\n", iFindElement(arr, N, key));
	return 0;
}