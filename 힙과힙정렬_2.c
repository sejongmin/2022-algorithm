#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define SIZE 100

typedef struct {
	int H[SIZE];
	int N;
}Heap;

void init(Heap* heap) {
	heap->N = 0;
	for (int i = 0; i < SIZE; i++)
		heap->H[i] = 0;
}

void insertItem(Heap* heap, int K) {
	heap->N++;
	heap->H[heap->N] = K;
}

void downHeap(Heap* heap, int i) {
	if (i * 2 > heap->N)
		return;
	if (heap->H[i] < heap->H[i * 2] || heap->H[i] < heap->H[i * 2 + 1]) {
		if (heap->H[i * 2] > heap->H[i * 2 + 1]) {
			int temp = heap->H[i];
			heap->H[i] = heap->H[i * 2];
			heap->H[i * 2] = temp;
			downHeap(heap, i * 2);
		}
		else {
			int temp = heap->H[i];
			heap->H[i] = heap->H[i * 2 + 1];
			heap->H[i * 2 + 1] = temp;
			downHeap(heap, i * 2 + 1);
		}
	}
	else {
		return;
	}
}

void rBuildHeap(Heap* heap, int i) {
	if (i > heap->N)
		return;

	if (i * 2 <= heap->N)
		rBuildHeap(heap, i * 2);
	if (i * 2 + 1 <= heap->N)
		rBuildHeap(heap, i * 2 + 1);

	downHeap(heap, i);
}

void printHeap(Heap* heap) {
	for (int i = 1; i <= heap->N; i++)
		printf(" %d", heap->H[i]);
	printf("\n");
}

int main() {
	Heap heap;
	init(&heap);

	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int num;
		scanf("%d", &num);
		insertItem(&heap, num);
	}

	rBuildHeap(&heap, 1);
	printHeap(&heap);

	return 0;
}