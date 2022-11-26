#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define FALSE 0
#define TRUE 1
#define INF 100000

typedef struct Edge {
	int weight;
	int v1, v2;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	int aName;
	struct IncidentEdge* next;
	Edge* e;
}IncidentEdge;

typedef struct Vertex {
	int vName;
	struct Vertex* next;
	IncidentEdge* iHead;
	int isVisit;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

void init(GraphType* G) {
	G->vHead = NULL;
	G->eHead = NULL;
	G->eCount = G->vCount = 0;
}

void makeVertex(GraphType* G, int vName) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = NULL;
	v->isVisit = FALSE;

	G->vCount++;

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

void makeIncidentEdge(Vertex* v, char aName, Edge* e)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->e = e;
	p->next = NULL;

	IncidentEdge* q = v->iHead;
	if (q == NULL)
		v->iHead = p;
	else {
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}


void insertEdge(GraphType* G, int vName1, int vName2, int w) {
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = vName1;
	e->v2 = vName2;
	e->weight = w;
	e->next = NULL;

	G->eCount++;

	Edge* p = G->eHead;
	if (p == NULL)
		G->eHead = e;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = e;
	}

	Vertex* v = findVertex(G, vName1);
	makeIncidentEdge(v, vName2, e);
	v = findVertex(G, vName2);
	makeIncidentEdge(v, vName1, e);
}

int getMinVertex(GraphType* G, int* dist) {
	Vertex* p = G->vHead;
	char vName;

	for (; p != NULL; p = p->next) {
		if (p->isVisit == FALSE) {
			vName = p->vName;
			break;
		}
	}

	for (p = G->vHead; p != NULL; p = p->next)
		if (p->isVisit == FALSE && dist[p->vName] < dist[vName])
			vName = p->vName;

	return vName;
}

void prim_Jarnik(GraphType* G, int vName, int* dist) {
	Vertex* p = findVertex(G, vName);
	IncidentEdge* q;
	int a;

	dist[p->vName] = 0;

	for (int i = 0; i < G->vCount; i++) {
		a = getMinVertex(G, dist);
		p = findVertex(G, a);
		p->isVisit = TRUE;
		printf(" %d", p->vName);

		for (q = p->iHead; q != NULL; q = q->next) {
			p = findVertex(G, q->aName);
			if (p->isVisit == FALSE && dist[p->vName] > q->e->weight)
				dist[p->vName] = q->e->weight;
		}
	}
}

int main() {
	GraphType G;
	init(&G);

	int N, M;
	int vName1, vName2, w, sum = 0;
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++)
		makeVertex(&G, i);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &vName1, &vName2, &w);
		insertEdge(&G, vName1, vName2, w);
	}

	int* dist = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 1; i <= N; i++)
		dist[i] = INF;

	prim_Jarnik(&G, 1, dist);
	for (int i = 1; i <= N; i++)
		sum += dist[i];
	printf("\n%d", sum);

	free(dist);

	return 0;
}