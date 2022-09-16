#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void selectF(int* arr, int N) {

	for (int i = 0; i < N; i++) {
		int maxidx = 0;
		for (int j = 0; j < N - i; j++) {
			if (arr[j] > arr[maxidx]) {
				maxidx = j;
			}
		}

		int temp = arr[N - i - 1];
		arr[N - i - 1] = arr[maxidx];
		arr[maxidx] = temp;
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

	selectF(arr, N);

	return 0;
}