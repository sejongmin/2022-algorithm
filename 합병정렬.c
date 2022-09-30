#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct ListNode {
	int data;
	struct ListNode* next;
}ListNode;

typedef struct {
	ListNode* H;
}ListType;

void init(ListType *L) {
	L->H = NULL;
}

ListNode* addNode(int e) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = e;
	node->next = NULL;

	return node;
}

void printList(ListType* L) {
	for (ListNode* p = L->H; p != NULL; p = p->next)
		printf(" %d", p->data);
	printf("\n");
}

void partition(ListType *L, ListType* L1, ListType* L2, int N) {
	ListNode* p = L->H;
	L1->H = p;
	for (int i = 0; i < N / 2 - 1; i++)
		p = p->next;
	L2->H = p->next;
	p->next = NULL;
}

void merge(ListType* L, ListType* L1, ListType* L2) {
	ListNode* p1 = L1->H;
	ListNode* p2 = L2->H;

	if (p1->data <= p2->data) {
		L->H = addNode(p1->data);
		p1 = p1->next;
	}
	else {
		L->H = addNode(p2->data);
		p2 = p2->next;
	}

	ListNode* p = L->H;

	while (p1 != NULL && p2 != NULL) {
		if (p1->data <= p2->data) {
			p->next = addNode(p1->data);
			p = p->next;
			p1 = p1->next;
		}
		else {
			p->next = addNode(p2->data);
			p = p->next;
			p2 = p2->next;
		}
	}
	while (p1 != NULL) {
		p->next = addNode(p1->data);
		p = p->next;
		p1 = p1->next;
	}
	while (p2 != NULL) {
		p->next = addNode(p2->data);
		p = p->next;
		p2 = p2->next;
	}
}

void mergeSort(ListType *L, int N) {
	if (L->H == NULL || L->H->next == NULL)
		return;

	ListType* L1;
	ListType* L2;
	init(&L1);
	init(&L2);

	partition(L, &L1, &L2, N);

	if (N % 2 == 0) {
		mergeSort(&L1, N / 2);
		mergeSort(&L2, N / 2);
	}
	else {
		mergeSort(&L1, N / 2);
		mergeSort(&L2, N / 2 + 1);
	}
	merge(L, &L1, &L2);
}


int main() {
	ListType L;
	init(&L);

	int N, num;
	scanf("%d", &N);
	scanf("%d", &num);
	L.H = addNode(num);

	ListNode* p = L.H;

	for (int i = 1; i < N; i++) {
		scanf("%d", &num);
		p->next = addNode(num);
		p = p->next;
	}

	mergeSort(&L, N);
	printList(&L);

	return 0;
}

