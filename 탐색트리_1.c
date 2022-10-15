#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct TreeNode {
	int key;
	struct TreeNode* parent, * lchild, * rchild;
}TreeNode;

void init(TreeNode* root) {
	root->parent = NULL;
	root->lchild = NULL;
	root->rchild = NULL;
}

int isExternal(TreeNode* root) {
	return (root->lchild == NULL && root->rchild == NULL);
}

int isRoot(TreeNode* root) {
	return root->parent == NULL;
}

TreeNode* treeSearch(TreeNode* v, int data) {
	if (isExternal(v))
		return v;
	if (v->key == data)
		return v;

	else if (data < v->key)
		return treeSearch(v->lchild, data);
	else if (data > v->key)
		return treeSearch(v->rchild, data);
}

void expandExternal(TreeNode* w) {
	TreeNode* left = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* right = (TreeNode*)malloc(sizeof(TreeNode));

	left->lchild = left->rchild = NULL;
	right->lchild = right->rchild = NULL;
	left->parent = right->parent = w;

	w->lchild = left;
	w->rchild = right;
}

void insertItem(TreeNode* root, int data) {
	TreeNode* w = treeSearch(root, data);
	if (!isExternal(w))
		return;

	w->key = data;
	expandExternal(w);
}

TreeNode* sibling(TreeNode* z) {
	if (z->parent->lchild == z)
		return z->parent->rchild;
	else
		return z->parent->lchild;
}

void reduceExternal(TreeNode* root, TreeNode* z) {
	TreeNode* w = z->parent;
	TreeNode* g = w->parent;
	TreeNode* zs = sibling(z);
	zs->parent = g;

	if (g == NULL)
		*root = *zs;
	else {
		if (w == g->lchild)
			g->lchild = zs;
		else
			g->rchild = zs;
	}
}

TreeNode* inOrderSucc(TreeNode* w) {
	w = w->rchild;

	while (w->lchild != NULL)
		w = w->lchild;

	return w;
}

int removeElement(TreeNode* root, int key) {
	TreeNode* w, * z, * y;
	w = treeSearch(root, key);

	if (isExternal(w))
		return -1;

	z = w->lchild;
	if (!isExternal(z))
		z = w->rchild;

	if (isExternal(z))
		reduceExternal(root, z);
	else {
		z = inOrderSucc(w);
		y = z->parent;
		w->key = y->key;
		reduceExternal(root, z);
	}

	return key;
}


void preOrder(TreeNode* root) {
	if (isExternal(root))
		return;

	printf(" %d", root->key);
	preOrder(root->lchild);
	preOrder(root->rchild);

}


int main() {
	TreeNode root;
	init(&root);

	char order;
	int data;
	int del;

	while (1) {
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &data);
			insertItem(&root, data);
			break;
		case 'd':
			scanf("%d", &data);
			del = removeElement(&root, data);
			if (del != -1)
				printf("%d\n", del);
			else
				printf("X\n");
			break;
		case 's':
			scanf("%d", &data);
			if (isExternal(treeSearch(&root, data)))
				printf("X\n");
			else
				printf("%d", data);
			break;
		case 'p':
			preOrder(&root);
			printf("\n");
			break;
		case 'q':
			return;
		default:
			break;
		}
		getchar();
	}
	return 0;
}