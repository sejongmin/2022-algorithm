#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define FALSE 0
#define TRUE 1


typedef struct IncidentEdge {
	int aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int vName;
	int isVisit;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct {
	Vertex* vHead;
}GraphType;


void initGraph(GraphType* G) {
	G->vHead = NULL;
}

void makeVertex(GraphType* G, int vName) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->isVisit = FALSE;
	v->next = NULL;
	v->iHead = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	v->iHead->next = NULL;

	Vertex* p = G->vHead;

	if (p == NULL)
		G->vHead = v;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}
}

Vertex* findVertex(GraphType* G, int vName) {
	Vertex* v = G->vHead;
	while (v->vName != vName)
		v = v->next;
	return v;
}

void makeIncidentEdge(Vertex* v, int aName) {
	IncidentEdge* i = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	i->aName = aName;
	i->next = NULL;

	IncidentEdge* p = v->iHead;
	if (p->next == NULL)
		v->iHead->next = i;
	else {
		while (p->next != NULL && p->next->aName < aName)
			p = p->next;
		if (p->next != NULL) {
			i->next = p->next;
			p->next = i;
		}
		else
			p->next = i;
	}
}

void insertEdge(GraphType* G, int v1, int v2) {
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);
	v = findVertex(G, v2);
	makeIncidentEdge(v, v1);
}

typedef struct {
	Vertex** queue;
	int front, rear;
}QueueType;

void initQueue(QueueType* Q, int N) {
	Q->front = Q->rear = 0;
	Q->queue = (Vertex*)malloc(sizeof(Vertex) * N);
}


int isQueueEmpty(QueueType* Q) {
	return Q->front == Q->rear;
}

void enqueue(QueueType* Q, Vertex* v, int N) {
	Q->rear = (Q->rear + 1) % N;
	Q->queue[Q->rear] = v;
}

Vertex* dequeue(QueueType* Q, int N) {
	Q->front = (Q->front + 1) % N;
	return Q->queue[Q->front];
}

void bfs(GraphType* G, int vName, int N) {
	Vertex* v = findVertex(G, vName);
	IncidentEdge* p;

	QueueType Q;
	initQueue(&Q, N);

	v->isVisit = TRUE;
	printf("%d\n", v->vName);
	enqueue(&Q, v, N);

	while (!isQueueEmpty(&Q)) {
		v = dequeue(&Q, N);
		for (p = v->iHead->next; p != NULL; p = p->next) {
			v = findVertex(G, p->aName);
			if (v->isVisit == FALSE) {
				v->isVisit = TRUE;
				printf("%d\n", v->vName);
				enqueue(&Q, v, N);
			}
		}
	}
}

int main() {
	GraphType G;
	initGraph(&G);

	int N, M, S;
	scanf("%d %d %d", &N, &M, &S);

	for (int i = 1; i <= N; i++)
		makeVertex(&G, i);

	int v1, v2;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &v1, &v2);
		insertEdge(&G, v1, v2);
	}

	bfs(&G, S, N);
	return 0;
}