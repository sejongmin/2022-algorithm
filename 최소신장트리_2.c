#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Edge {
	int weight;
	int v1, v2;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	int aName;
	struct IncidentEdge* next;
	Edge *e;
}IncidentEdge;

typedef struct Vertex {
	int vName;
	struct Vertex* next;
	IncidentEdge *iHead;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	int vCount;
	int eCount;
}GraphType;

void init(GraphType *G) {
	G->vHead = NULL;
	G->eHead = NULL;
	G->eCount = G->vCount = 0;
}

void makeVertex(GraphType* G, int vName) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = NULL;

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
	else{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}


void insertEdge(GraphType *G, int vName1, int vName2, int w) {
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

int inPlacePartition(Edge* e[], int left, int right) {
	int low = left - 1;
	int high = right;
	int pivot = e[right]->weight;
	Edge* tmp;

	do{
		do { low++; } while (pivot > e[low]->weight);
		do { high--; } while (high > 0 && pivot < e[high]->weight);
		if (low < high) {
			tmp = e[low];
			e[low] = e[high];
			e[high] = tmp;
		}
	} while (low < high);

	tmp = e[low];
	e[low] = e[right];
	e[right] = tmp;

	return low;
}

void QuickSort(Edge* e[], int left, int right) {
	if (left >= right)
		return;
	int q = inPlacePartition(e, left, right);
	QuickSort(e, left, q - 1);
	QuickSort(e, q + 1, right);
}

void eSort(GraphType* G, Edge* e[]) {
	Edge* p = G->eHead;

	for (int i = 0; i < G->eCount; i++, p = p->next)
		e[i] = p;

	QuickSort(e, 0, G->eCount - 1);
}

int rFind(int* v, int vNum) {
	if (v[vNum] == 0)
		return vNum;

	while (v[vNum] != 0)
		vNum = v[vNum];

	return vNum;
}

void vUnion(int v[], int vNum1, int vNum2)
{
	int r1 = rFind(v, vNum1);
	int r2 = rFind(v, vNum2);

	v[r2] = r1;
}


void kruskal(GraphType *G, Edge* e[], int* v) {
	int eCnt = 0, i = 0, sum = 0;

	while (eCnt < G->vCount-1) {
		int v1 = e[i]->v1;
		int v2 = e[i]->v2;

		int vNum1 = rFind(v, v1);
		int vNum2 = rFind(v, v2);

		if (vNum1 != vNum2) {
			eCnt++;
			printf(" %d", e[i]->weight);
			sum += e[i]->weight;
			vUnion(v, vNum1, vNum2);
		}
		i++;
	}
	printf("\n%d", sum);
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
	
	Edge* e = (Edge*)malloc(M * sizeof(Edge));
	eSort(&G, e);

	int* v = (int*)calloc(N + 1, sizeof(int));
	kruskal(&G, e, v);

	free(e);
	free(v);

	return 0;
}