#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int inPlacePartition(int* arr, int left, int right, int k) {
	int low, high, pivot, temp;
	pivot = arr[k];
	SWAP(arr[k], arr[right], temp);

	low = left - 1;
	high = right;
	do {
		do {
			low++;
		} while (arr[low] < pivot);

		do {
			high--;
		} while (arr[high] > pivot);

		if (low < high)
			SWAP(arr[low], arr[high], temp);

	} while (low < high);
	SWAP(arr[low], arr[right], temp);
	return low;
}

void inPlaceQuickSort(int* arr, int left, int right) {
	if (left >= right)
		return;
	int k = rand() % (right - left + 1) + left;
	int q = inPlacePartition(arr, left, right, k);
	inPlaceQuickSort(arr, left, q - 1);
	inPlaceQuickSort(arr, q + 1, right);
}

void printList(int* arr, int N) {
	for (int i = 0; i < N; i++)
		printf(" %d", arr[i]);
	printf("\n");
}

int main() {
	srand(time(NULL));

	int N;
	scanf("%d", &N);
	
	int* arr = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++) 
		scanf("%d", &arr[i]);

	inPlaceQuickSort(arr, 0, N - 1);
	printList(arr, N);

	return 0;
}