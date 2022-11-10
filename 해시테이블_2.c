#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int h(int v, int M) {
	return v % M;
}

int insertItem(int* arr, int k, int M) {
	int b = h(k, M);
	int count = 0;

	while (arr[b] != 0) {
		count++;
		b = (b + 1) % M;
	}
	arr[b] = k;
	return count;
}

int findElement(int* arr, int k, int M) {
	int b = h(k, M);
	while (arr[b] != 0) {
		if (arr[b] == k)
			return b;
		b = (b + 1) % M;
	}
	return -1;
}


int main() {
	int M, N;
	scanf("%d %d", &M, &N);

	int* arr = (int*)calloc(M, sizeof(int));

	char order;
	int data, cnt, f;
	while (1) {
		getchar();
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &data);
			cnt = insertItem(arr, data, M);
			for (int i = 0; i < cnt; i++)
				printf("C");
			printf("%d\n", (h(data, M) + cnt) % M);
			break;
		case 's':
			scanf("%d", &data);
			f = findElement(arr, data, M);
			if (f == -1)
				printf("-1\n");
			else
				printf("%d %d\n", findElement(arr, data, M), data);
			break;
		case 'e':
			return;
		}
	}
}