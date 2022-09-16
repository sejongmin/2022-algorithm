#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct DListNode {
	char elem;
	struct DListNode* prev, * next;
}DListNode;

typedef struct DListType {
	DListNode* H, * T;
}DListType;

void init(DListType* DL) {
	DL->H = DL->T = NULL;
}

int isEmpty(DListType* DL) {
	return DL->H == NULL;
}

void insertFirst(DListType* DL, char e) {
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));
	node->elem = e;
	node->next = node->prev = NULL;

	if (isEmpty(DL))
		DL->H = DL->T = node;
	else {
		DListNode* p = DL->H;
		p->prev = node;
		node->next = p;
		DL->H = node;
	}
	return;
}

void insertLast(DListType* DL, char e) {
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));
	node->elem = e;
	node->next = node->prev = NULL;

	DListNode* p = DL->T;
	p->next = node;
	node->prev = p;
	DL->T = node;

	return;
}

void add(DListType* DL, int r, char e) {
	if (r == 1) {
		insertFirst(DL, e);
		return;
	}
	else {
		if (isEmpty(DL)) {
			printf("invalid position\n");
			return;
		}
		DListNode* node = (DListNode*)malloc(sizeof(DListNode));
		node->elem = e;
		node->next = node->prev = NULL;

		DListNode* p = DL->H;

		for (int i = 2; i < r; i++) {
			p = p->next;
			if (p == NULL) {
				printf("invalid position\n");
				return;
			}
		}
		if (p == DL->T) {
			insertLast(DL, e);
			return;
		}
		node->next = p->next;
		node->prev = p;
		p->next->prev = node;
		p->next = node;

		return;
	}
}

char deleteFirst(DListType* DL) {
	if (isEmpty(DL)) {
		printf("invalid position\n");
		return;
	}
	DListNode* p = DL->H;
	char e = p->elem;

	if (p == DL->T)
		DL->H = DL->T = NULL;
	else {
		p->next->prev = NULL;
		DL->H = p->next;
	}
	free(p);
	return e;
}

char deleteLast(DListType* DL) {
	DListNode* p = DL->T;
	char e = p->elem;

	p->prev->next = NULL;
	DL->T = p->prev;

	free(p);
	return e;
}

char delete(DListType* DL, int r) {
	if (r == 1)
		return deleteFirst(DL);
	else {
		if (isEmpty(DL)) {
			printf("invalid position\n");
			return;
		}
		DListNode* p = DL->H;
		for (int i = 1; i < r; i++) {
			p = p->next;
			if (p == NULL) {
				printf("invalid position\n");
				return;
			}
		}
		char e = p->elem;
		if (p == DL->T) {
			return deleteLast(DL);
		}

		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);

		return e;
	}
}

void get_entry(DListType* DL, int r) {
	if (isEmpty(DL)) {
		printf("invalid position\n");
		return;
	}
	DListNode* p = DL->H;
	for (int i = 1; i < r; i++) {
		p = p->next;
		if (p == NULL) {
			printf("invalid position\n");
			return;
		}
	}
	printf("%c\n", p->elem);
}

void Print(DListType* DL) {
	for (DListNode* p = DL->H; p != NULL; p = p->next)
		printf("%c", p->elem);
	printf("\n");
}

int main() {
	DListType DL;
	init(&DL);

	int N;
	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {
		char o;
		scanf("%c", &o);

		if (o == 'A') {
			int rank;
			char data;
			scanf("%d %c", &rank, &data);
			add(&DL, rank, data);
		}
		else if (o == 'D') {
			int rank;
			scanf("%d", &rank);
			delete(&DL, rank);
		}
		else if (o == 'G') {
			int rank;
			scanf("%d", &rank);
			get_entry(&DL, rank);
		}
		else if (o == 'P') {
			Print(&DL);
		}
		getchar();
	}
	return 0;
}