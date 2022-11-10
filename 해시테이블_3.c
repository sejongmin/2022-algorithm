#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int h(int v, int M) {
	return v % M;
}

int h2(int q, int v) {
	return q - (v % q);
}
int getNextBucketDouble(int v, int i, int q, int M) {
	return (v + i * h2(q, v)) % M;
}
int insertItem(int* arr, int k, int M, int q) {
	int b = h(k, M);
	int count = 0;

	while (arr[b] != 0) {
		count++;
		b = getNextBucketDouble(k, count, q, M);
	}
	arr[b] = k;
	return count;
}

int findElement(int* arr, int k, int q, int M) {
	int b = h(k, M);
	int count = 0;
	while (arr[b] != 0) {
		if (arr[b] == k)
			return b;
		count++;
		b = getNextBucketDouble(k, count, q, M);
	}
	return -1;
}

void print(int* arr, int M) {
	for (int i = 0; i < M; i++)
		printf(" %d", arr[i]);
	printf("\n");
}


int main() {
	int M, N, q;
	scanf("%d %d %d", &M, &N, &q);

	int* arr = (int*)calloc(M, sizeof(int));

	char order;
	int data, cnt, f, idx;

	while (1) {
		getchar();
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &data);
			cnt = insertItem(arr, data, M, q);
			idx = h(data, M);
			for (int i = 0; i < cnt; i++)
				printf("C");
			printf("%d\n", getNextBucketDouble(data, cnt, q, M));
			break;
		case 's':
			scanf("%d", &data);
			f = findElement(arr, data, q, M);
			if (f == -1)
				printf("-1\n");
			else
				printf("%d %d\n", findElement(arr, data, q, M), data);
			break;
		case 'p':
			print(arr, M);
			break;
		case 'e':
			print(arr, M);
			free(arr);
			return;
		}
	}
}