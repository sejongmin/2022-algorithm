#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void insertF(int* arr, int N) {

	for (int i = 1; i < N; i++) {
		int key = arr[i];
		int j = i - 1;
		while (arr[j] > key && j >= 0) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
	for (int i = 0; i < N; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}


int main() {
	int N;
	scanf("%d", &N);
	int* arr = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	insertF(arr, N);

	return 0;
}