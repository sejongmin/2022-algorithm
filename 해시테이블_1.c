#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct ListNode {
	int data;
	struct Bucket* next;
}ListNode;

void init(ListNode* H, int M) {
	for (int i = 0; i < M; i++) {
		H[i].data = 0;
		H[i].next = NULL;
	}
}

int h(int x, int M) {
	return x % M;
}

void insert(ListNode* H, int data, int M) {
	int b = h(data, M);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;

	node->next = H[b].next;
	H[b].next = node;
}

int search(ListNode* H, int data, int M) {
	int b = h(data, M);
	int count = 0;
	ListNode* p = H[b].next;

	while (p != NULL) {
		count++;
		if (p->data == data)
			return count;

		p = p->next;
	}

	return 0;
}

int delete(ListNode* H, int data, int M) {
	int b = h(data, M);
	int count = 0;
	ListNode* p = H[b].next;
	ListNode* q = p;

	while (p != NULL) {
		count++;
		if (p->data == data) {
			if (count == 1) {
				H[b].next = p->next;
				free(p);
				return count;
			}
			else {
				q->next = p->next;
				free(p);
				return count;
			}
		}
		q = p;
		p = p->next;
	}

	return 0;
}

void print(ListNode* H, int M) {
	for (int i = 0; i < M; i++) {
		ListNode* p = H[i].next;
		while (p != NULL) {
			printf(" %d", p->data);
			p = p->next;
		}
	}
	printf("\n");
}


int main() {
	int M;
	scanf("%d", &M);

	ListNode* H = (ListNode*)malloc(sizeof(ListNode) * M);
	init(H, M);

	char order;
	int data;

	while (1) {
		getchar();
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &data);
			insert(H, data, M);
			break;
		case 's':
			scanf("%d", &data);
			printf("%d\n", search(H, data, M));
			break;
		case 'd':
			scanf("%d", &data);
			printf("%d\n", delete(H, data, M));
			break;
		case 'p':
			print(H, M);
			break;
		case 'e':
			return;
		default:
			break;
		}
	}

	return 0;
}