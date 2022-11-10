#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Edge {
	int weight;
	int v1, v2;
	struct Edge* next;
}Edge;

typedef struct IncidentVertex {
	int adjVertex;
	Edge* e;
	struct IncidentVertex* next;
}IncidentVertex;

typedef struct Vertex {
	int vName;
	IncidentVertex* iHead;
	struct Vertex* next;
}Vertex;

typedef struct {
	Edge* eHead;
	Vertex* vHead;
}Graph;

void init(Graph* G) {
	G->eHead = NULL;
	G->vHead = NULL;
}

void makeVertex(Graph* G, int vName) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->iHead = NULL;
	v->next = NULL;

	Vertex* p = G->vHead;
	if (p == NULL)
		G->vHead = v;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}
}

Vertex* findVertex(Graph* G, int vName) {
	Vertex* p = G->vHead;
	while (p != NULL && p->vName != vName)
		p = p->next;

	return p;
}


void insertIncidentVertex(Vertex* v, int av, Edge* e) {
	IncidentVertex* i = (IncidentVertex*)malloc(sizeof(IncidentVertex));
	i->adjVertex = av;
	i->e = e;
	i->next = NULL;

	IncidentVertex* p = v->iHead;
	if (p == NULL)
		v->iHead = i;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = i;
	}
}

void insertEdge(Graph* G, int w, int v1, int v2) {
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = v1;
	e->v2 = v2;
	e->weight = w;
	e->next = NULL;

	Edge* q = G->eHead;
	if (q == NULL)
		G->eHead = e;
	else {
		while (q->next != NULL)
			q = q->next;
		q->next = e;
	}
	Vertex* p = findVertex(G, v1);
	insertIncidentVertex(p, v2, e);
	p = findVertex(G, v2);
	insertIncidentVertex(p, v1, e);
}

void modifyWeight(Graph* G, int v1, int v2, int w) {
	Vertex* p = findVertex(G, v1);
	IncidentVertex* r = p->iHead;

	while (r != NULL && r->adjVertex != v2) {
		r = r->next;
	}
	if (r == NULL)
		insertEdge(G, w, v1, v2);
	else
		r->e->weight = w;
}

void printVertex(Graph* G, int vName) {
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	IncidentVertex* r = p->iHead;

	int* arr = (int*)calloc(7, sizeof(int));
	for (; r != NULL; r = r->next)
		arr[r->adjVertex] = r->e->weight;

	for (int i = 1; i <= 6; i++) {
		if (arr[i] != 0)
			printf(" %d %d", i, arr[i]);
	}
	printf("\n");
}

int main()
{
	Graph G;
	init(&G);

	for (int i = 1; i <= 6; i++)
		makeVertex(&G, i);

	insertEdge(&G, 1, 1, 2);
	insertEdge(&G, 1, 1, 3);
	insertEdge(&G, 1, 1, 4);
	insertEdge(&G, 2, 1, 6);
	insertEdge(&G, 1, 2, 3);
	insertEdge(&G, 4, 3, 5);
	insertEdge(&G, 4, 5, 5);
	insertEdge(&G, 3, 5, 6);

	char order;
	int v1, v2, w;

	while (1) {
		scanf("%c", &order);
		switch (order) {
		case 'a':
			scanf("%d", &v1);
			if (v1 >= 1 && v1 <= 6)
				printVertex(&G, v1);
			else
				printf("-1\n");
			break;
		case 'm':
			scanf("%d %d %d", &v1, &v2, &w);
			if ((v1 >= 1 && v1 <= 6) && (v2 >= 1 && v2 <= 6))
				modifyWeight(&G, v1, v2, w);
			else
				printf("-1\n");
			break;
		case 'q':
			return 0;
		default:
			break;
		}
		getchar();
	}

	return 0;
}