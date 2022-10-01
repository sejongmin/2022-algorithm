#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void makeList(char *arr, int N) {
	for (int i = 0; i < N; i++) {
		int K = rand() % 3;
		switch (K) {
		case 0:
			arr[i] = 'R';
			break;
		case 1:
			arr[i] = 'G';
			break;
		case 2:
			arr[i] = 'B';
			break;
		}
	}
}

void printList(char* arr, int N) {
	for (int i = 0; i < N; i++) 
		printf("[%c]", arr[i]);
	printf("\n");
}

int inPlacePartition(char* arr, int left, int right, int K) {
	int low, high, pivot ,temp;
	low = left - 1;
	high = right;
	pivot = arr[K];
	SWAP(arr[right], arr[K], temp);
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

void inPlaceQuick(char* arr, int left, int right) {

	if (left > right)
		return;
	int K = rand() % (right - left + 1) + left;
	int q = inPlacePartition(arr, left, right, K);
	inPlaceQuick(arr, left, q-1);
	inPlaceQuick(arr, q + 1, right);

}

int main() {
	srand(time(NULL));
	int N;
	printf("·£´ý »ö±òÀÇ °øÀÇ °³¼ö : ");
	scanf("%d", &N);

	char* arr = (char*)malloc(sizeof(char) * (N + 1));
	makeList(arr, N);
	printList(arr, N);

	inPlaceQuick(arr, 0, N - 1);
	printList(arr, N);

	return 0;

}