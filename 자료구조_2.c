#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

typedef struct StackNode {
	TreeNode* elem;
	struct StackNode* next;
}StackNode;

typedef struct {
	StackNode* T;
}Stack;

void init(TreeNode* root, Stack* S) {
	root->left = root->right = NULL;
	S->T = NULL;
}

int isEmpty(Stack* S) {
	return S->T == NULL;
}

void push(Stack* S, TreeNode* R) {
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->elem = R;
	node->next = NULL;

	if (isEmpty(S))
		S->T = node;
	else {
		node->next = S->T;
		S->T = node;
	}
	return;
}

TreeNode* pop(Stack* S) {
	StackNode* p = S->T;
	TreeNode* e = p->elem;

	S->T = p->next;
	p->next = NULL;
	free(p);

	return e;
}

void makeNode(TreeNode* root, Stack* S, int l, int r) {
	TreeNode* lnode = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* rnode = (TreeNode*)malloc(sizeof(TreeNode));

	if (r != 0) {
		rnode->data = r;
		push(S, rnode);
	}
	else
		rnode = NULL;
	if (l != 0) {
		lnode->data = l;
		push(S, lnode);
	}
	else
		lnode = NULL;


	root->left = lnode;
	root->right = rnode;
}


void makeTree(TreeNode* root) {
	Stack S;
	S.T = NULL;

	int N, d, l, r;
	scanf("%d", &N);
	scanf("%d %d %d", &d, &l, &r);

	root->data = d;
	makeNode(root, &S, l, r);

	for (int i = 1; i < N; i++) {
		scanf("%d %d %d", &d, &l, &r);
		if (!isEmpty(&S)) {
			TreeNode* p = pop(&S);
			makeNode(p, &S, l, r);
		}
	}
}

void print(TreeNode* root, char* str) {
	printf(" %d", root->data);
	if (*str == 'L')
		print(root->left, str + 1);
	else if (*str == 'R')
		print(root->right, str + 1);
	else return;
}


int main() {
	TreeNode root;
	makeTree(&root);

	int T;
	scanf("%d", &T);
	getchar();
	for (int i = 0; i < T; i++) {
		char str[101];
		scanf("%s", str);
		getchar();
		print(&root, str);
		printf("\n");
	}
	return 0;
}