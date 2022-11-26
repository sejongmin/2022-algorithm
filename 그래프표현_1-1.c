#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define FALSE 0
#define TRUE 1


typedef struct Edge {
	int weight;
	int v1;
	int v2;
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
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
}Graph;

void initGraph(Graph *G) {
	G->vHead = NULL;
	G->eHead = NULL;
}

Vertex* findVertex(Graph *G, int vName) {
	Vertex* p = G->vHead;
	while (p != NULL && p->vName != vName)
		p = p->next;

	return p;
}

void makeVertex(Graph *G, int vName) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	v->iHead->next = NULL;

	Vertex* p = G->vHead;
	if (p == NULL)
		G->vHead = v;
	else {
		while (p->next != NULL && p->next->vName < vName)
			p = p->next;
		v->next = p->next;
		p->next = v;
	}
}

void insertIncidentEdge(Vertex* v, int aName, Edge* e) {
	IncidentEdge* i = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	i->aName = aName;
	i->e = e;
	i->next = NULL;

	IncidentEdge* p = v->iHead;
	while (p->next != NULL && p->next->aName < aName)
		p = p->next;
	i->next = p->next;
	p->next = i;
}

void insertEdge(Graph* G, int w, int vName1, int vName2) {
	Vertex* v1 = findVertex(G, vName1);
	Vertex* v2 = findVertex(G, vName2);
	if (v1 == NULL || v2 == NULL) {
		printf("-1\n");
		return;
	}

	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = vName1;
	e->v2 = vName2;
	e->weight = w;
	e->next = NULL;


	Edge* p = G->eHead;
	if (p == NULL)
		G->eHead = e;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = e;
	}

	insertIncidentEdge(v1, vName2, e);
	if (vName1 != vName2)
		insertIncidentEdge(v2, vName1, e);
}

void deleteEdge(Graph* G, int vName1, int vName2) {
	Vertex* v = findVertex(G, vName1);

	IncidentEdge* p = v->iHead->next;
	IncidentEdge* q = v->iHead;

	while (p->aName != vName2) {
		q = p;
		p = p->next;
	}
	q->next = p->next;
	
	Edge* m = G->eHead;
	Edge* n = m;
	if (m == p->e)
		G->eHead = m->next;
	else {
		while (m != p->e) {
			n = m;
			m = m->next;
		}
		n->next = m->next;
	}

	if (vName1 == vName2)
		return;

	v = findVertex(G, vName2);
	p = v->iHead->next;
	q = v->iHead;

	while (p->aName != vName1) {
		q = p;
		p = p->next;
	}
	q->next = p->next;

	free(p);
	free(m);
}

void modifyWeight(Graph* G, int w, int vName1, int vName2) {
	Vertex* v1 = findVertex(G, vName1);
	Vertex* v2 = findVertex(G, vName2);
	if (v1 == NULL || v2 == NULL) {
		printf("-1\n");
		return;
	}

	IncidentEdge* i = v1->iHead;

	if (w == 0) {
		while (i->next != NULL && i->next->aName < vName2)
			i = i->next;
		if (i->next->aName == vName2)
			deleteEdge(G, vName1, vName2);
		else
			return;
	}
	else {
		while (i->next != NULL && i->next->aName < vName2)
			i = i->next;
		if (i->next != NULL && i->next->aName == vName2)
			i->next->e->weight = w;
		else
			insertEdge(G, w, vName1, vName2);
	}
}

void printVertex(Graph* G, int vName) {
	Vertex* p = G->vHead;
	while (p != NULL && p->vName != vName)
		p = p->next;
	if (p == NULL) {
		printf("-1\n");
		return;
	}

	IncidentEdge* r = p->iHead;
	for (; r->next != NULL; r = r->next)
		printf(" %d %d", r->next->aName, r->next->e->weight);
	printf("\n");
}

int main() {
	Graph G;
	initGraph(&G);

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
			printVertex(&G, v1);
			break;
		case 'm':
			scanf("%d %d %d", &v1, &v2, &w);
			modifyWeight(&G, w, v1, v2);
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