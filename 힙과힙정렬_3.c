#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void insertItem(Heap* heap, int key) {
	heap->N++;
	heap->H[heap->N] = key;
}

void downHeap(Heap* heap, int i) {
	int k = heap->H[i];
	int p = i, c = i * 2;

	while (c <= heap->N) {
		if ((c < heap->N) && (heap->H[c] < heap->H[c + 1]))
			c++;
		if (heap->H[c] <= k)
			break;
		heap->H[p] = heap->H[c];
		p = c;
		c = c * 2;
	}
	heap->H[p] = k;
}

void rBuildHeap(Heap* heap, int i) {
	if (heap->N < i)
		return;

	if (heap->N >= i * 2)
		rBuildHeap(heap, i * 2);
	if (heap->N >= i * 2 + 1)
		rBuildHeap(heap, i * 2 + 1);

	downHeap(heap, i);
}

int removeMax(Heap* heap) {
	int key = heap->H[1];
	heap->H[1] = heap->H[heap->N];
	heap->N--;
	downHeap(heap, 1);
	return key;
}

void inPlaceHeapSort(Heap* heap) {
	int size = heap->N;
	for (int i = 0; i < size; i++) {
		int key = removeMax(heap);
		heap->H[heap->N + 1] = key;
	}
}

void printArray(Heap* heap, int size) {
	for (int i = 1; i <= size; i++)
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
	inPlaceHeapSort(&heap);
	printArray(&heap, N);

	return 0;
}