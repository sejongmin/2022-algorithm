#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define SIZE 100

typedef struct {
	int N;
	int H[SIZE];
}Heap;

void init(Heap *heap) {
	heap->N = 0;
	return;
}

void upHeap(Heap* heap) {
	int K = heap->H[heap->N];
	int i = heap->N;

	while (i != 1 && heap->H[i / 2] < K) {
		heap->H[i] = heap->H[i / 2];
		i = i / 2;
	}
	heap->H[i] = K;
	return;
}

void downHeap(Heap* heap) {
	int K = heap->H[1];
	int p = 1, c = 2;

	while (c <= heap->N) {
		if (c < heap->N && heap->H[c] < heap->H[c + 1])
			c++;
		if (K > heap->H[c])
			break;
		heap->H[p] = heap->H[c];
		p = c;
		c = c * 2;
	}
	heap->H[p] = K;
	return;
}

void insertItem(Heap* heap, int K) {
	heap->N++;
	heap->H[heap->N] = K;
	upHeap(heap);
	return;
}

int removeMax(Heap* heap) {
	int K = heap->H[1];
	heap->H[1] = heap->H[heap->N];
	heap->N--;
	downHeap(heap);
	return K;
}

void printHeap(Heap* heap) {
	for (int i = 1; i <= heap->N; i++)
		printf(" %d", heap->H[i]);
	printf("\n");
}


int main() {
	Heap heap;
	init(&heap);

	int num;
	char order;

	while (1) {
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &num);
			insertItem(&heap, num);
			printf("0\n");
			break;
		case 'd':
			printf("%d\n", removeMax(&heap));
			break;
		case 'p':
			printHeap(&heap);
			break;
		case 'q':
			return 0;
		default :
			break;
		}
	}

	return 0;
}