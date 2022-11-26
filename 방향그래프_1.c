#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define SIZE 100

typedef struct {
	char elem[SIZE];
	int front, rear;
}QueueType;

typedef struct IncidentEdge {
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	char vName;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct {
	Vertex* vHead;
	int vCount;
}Graph;

void initQueue(QueueType* Q) {
	Q->front = Q->rear = 0;
}

void init(Graph* G) {
	G->vHead = NULL;
	G->vCount = 0;
}

int isEmpty(QueueType* Q) {
	return Q->rear == Q->front;
}

int isFull(QueueType* Q) {
	return (Q->rear + 1) % SIZE == Q->front;
}

void enqueue(QueueType* Q, char vName) {
	Q->rear = (Q->rear + 1) % SIZE;
	Q->elem[Q->rear] = vName;
}

char dequeue(QueueType* Q) {
	Q->front = (Q->front + 1) % SIZE;
	return Q->elem[Q->front];
}

void makeVertex(Graph* G, char vName) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->iHead = NULL;
	v->next = NULL;
	G->vCount++;

	Vertex* q = G->vHead;
	if (q == NULL)
		G->vHead = v;
	else {
		while (q->next != NULL)
			q = q->next;
		q->next = v;
	}
}

void makeIncidentEdge(Vertex* v, char aName) {
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	IncidentEdge* q = v->iHead;

	if (q != NULL)
		p->next = q;

	v->iHead = p;
}

Vertex* findVertex(Graph* G, char vName) {
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	return p;
}

void insertEdge(Graph* G, char v1, char v2) {
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);
}

int nameToNum(char node[], char Name) {
	int i = 0;
	while (node[i] != Name)
		i++;

	return i;
}

char numToName(char node[], int N) {
	return node[N];
}

void inDegree(Graph* G, int* in, char node[]) {
	Vertex* p = G->vHead;
	IncidentEdge* q;

	for (; p != NULL; p = p->next)
		for (q = p->iHead; q != NULL; q = q->next)
			in[nameToNum(node, q->aName)]++;
}

void topologicalSort(Graph* G, int* in, int N, char node[]) {
	QueueType Q;
	initQueue(&Q);

	char* topOrder = (char*)malloc(N + 1 * sizeof(char));
	int rank = 1;

	Vertex* p;
	IncidentEdge* q;

	inDegree(G, in, node);

	for (int i = 0; i < G->vCount; i++) {
		if (in[i] == 0)
			enqueue(&Q, numToName(node, i));
	}

	while (!isEmpty(&Q)) {
		char vName = dequeue(&Q);
		topOrder[rank++] = vName;

		p = findVertex(G, vName);
		q = p->iHead;

		while (q != NULL) {
			in[nameToNum(node, q->aName)]--;
			if (in[nameToNum(node, q->aName)] == 0)
				enqueue(&Q, q->aName);

			q = q->next;
		}
	}

	if (rank <= N)
		printf("0");
	else
		for (int i = 1; i <= N; i++)
			printf("%c ", topOrder[i]);
}


int main() {
	Graph G;
	init(&G);


	int N, M;
	char vName1, vName2;
	scanf("%d", &N);

	char* node = (char*)malloc(N * sizeof(char));
	int* in = (int*)calloc(N, sizeof(int));

	for (int i = 0; i < N; i++) {
		getchar();
		scanf("%c", &vName1);
		node[i] = vName1;
		makeVertex(&G, vName1);
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		getchar();
		scanf("%c %c", &vName1, &vName2);
		insertEdge(&G, vName1, vName2);
	}

	topologicalSort(&G, in, N, node);

	return 0;
}