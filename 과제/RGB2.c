#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void makeList(char* arr, int N) {
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

void QuickSort(char* arr, int N) {
	int low, high, temp;
	low = -1;
	high = N;
	//R ¶û B,G Á¤·Ä.
	do {
		do {
			low++;
		} while (arr[low] == 'R');

		do {
			high--;
		} while (arr[high] != 'R');

		if (low < high)
			SWAP(arr[low], arr[high], temp);

	} while (low < high);
	low--;
	high = N;
	//G ¶û B Á¤·Ä
	do {
		do {
			low++;
		} while (arr[low] != 'B');

		do {
			high--;
		} while (arr[high] == 'B');

		if (low < high)
			SWAP(arr[low], arr[high], temp);

	} while (low < high);
}


int main() {
	srand(time(NULL));
	int N;
	printf("·£´ý »ö±òÀÇ °øÀÇ °³¼ö : ");
	scanf("%d", &N);

	char* arr = (char*)malloc(sizeof(char) * (N + 1));
	makeList(arr, N);
	printf("Á¤·Ä Àü : ");
	printList(arr, N);

	QuickSort(arr, N);
	printf("Á¤·Ä ÈÄ : ");
	printList(arr, N);

	return 0;
}