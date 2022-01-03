#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
	struct Tree* lChild, * rChild, * parent;
	int key;
}tree;

int findElement(int k, tree* root);
void insertItem(int k, tree* root);
tree* treeSearch(int k, tree* root);
int removeElement(int k, tree** root);
int isExternal(tree* w);
int isInternal(tree* w);
tree* inOrderSucc(tree* w); // ��� w�� ������ȸ �İ��ڸ� ��ȯ
void printTree(tree* root);
tree* reduceExternal(tree** z, tree** root);
void expandExternal(tree* p);
tree* sibling(tree** w);

void makeTree(tree** p, tree* parent);
void freeTree(tree* p);

int main() {
	
	char c; 
	int k, X;
	tree* root = NULL, * Y = NULL;
	makeTree(&root, NULL); // root�� �θ���� ����.
	while (1) {
		scanf("%c", &c);
		switch (c)
		{
		case 'i':
			scanf("%d", &k);
			getchar();
			insertItem(k, root);
			break;
		case 'd':
			scanf("%d", &k);
			getchar();
			X = removeElement(k, &root);
			if (X != -1)
				printf("%d\n", X);
			break;
		case 's':
			scanf("%d", &k);
			getchar();
			Y = treeSearch(k, root);
			if (!isExternal(Y)) // �ܺγ�尡 �ƴҶ� ���
				printf("%d\n", Y->key);
			else
				printf("X\n");
			break;
		case 'p':
			printTree(root);
			printf("\n");
			break;
		case 'q':
			freeTree(root);
			return 0;
		}
	}
	freeTree(root);
	return 0;
}

int findElement(int k, tree* root) {
	tree* w = treeSearch(k, root);
	if (isExternal(root)) { // ã�� ����.
		printf("X\n");
		return -1;
	}
	else
		return w->key;
}

void insertItem(int k, tree* root) {

	tree* w = treeSearch(k, root); // k�� ���� ����� ���� �ܺ� ���� �̵��Ѵ�.
	if (isInternal(w))
		return;
	else {
		w->key = k;
		expandExternal(w); // �ܺγ��� Ȯ��
	}
}

tree* treeSearch(int k, tree* root) {
	if (isExternal(root))
		return root; 
	if (k == root->key)
		return root;
	else if (k > root->key) // �� ũ�� ���������� ���� Ž��
		return treeSearch(k, root->rChild);
	else // ������ �������� ���� Ž��
		return treeSearch(k, root->lChild);
}

int isExternal(tree* w) {
	if (w->lChild == NULL && w->rChild == NULL)
		return 1;
	else
		return 0;
}
int isInternal(tree* w) {
	if (w->lChild != NULL || w->rChild != NULL)
		return 1;
	else
		return 0;
}

tree* inOrderSucc(tree* w) {
	w = w->rChild; // ������ �ڽ� ���
	if (isExternal(w))
		return NULL;
	while (isInternal(w->lChild))
		w = w->lChild;
	return w;
}

void makeTree(tree** p, tree* parent) {
	tree* root = (tree*)malloc(sizeof(tree));
	root->parent = parent;
	root->lChild = NULL;
	root->rChild = NULL;
	*p = root;
}

void printTree(tree* root) {
	printf(" %d", root->key);
	if (!isExternal(root->lChild))
		printTree(root->lChild);
	if (!isExternal(root->rChild))
		printTree(root->rChild);
}

void freeTree(tree* p) {
	if (p->lChild != NULL)
		freeTree(p->lChild);
	if (p->rChild != NULL)
		freeTree(p->rChild);
	free(p);
}

int removeElement(int k, tree** root) {
	tree* w = treeSearch(k, *root); // ���� ��ġ ã�´�.
	if (isExternal(w)) {
		printf("X\n");
		return -1;
	}
	int e = w->key;
	tree* z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))
		reduceExternal(&z, root); // root�� ��ġ�� �������ؾ��� ���� ����
	else {
		tree* y = inOrderSucc(w);
		z = y->lChild; 
		w->key = y->key; // ����Ѵ�.
		reduceExternal(&z, root);
	}
	return e;
}

tree* sibling(tree** z) {
	if ((*z)->parent == NULL)
		return NULL; // ��Ʈ���� ������尡 ����.
	if ((*z)->parent->lChild == (*z)) // �Ķ���� ��尡 ���� ����̸� ��������� ������ ��� ��ȯ
		return (*z)->parent->rChild;
	else
		return (*z)->parent->lChild;
}

tree* reduceExternal(tree** z, tree** root) {
	tree* w = (*z)->parent;
	tree* zs = sibling(z);
	if (w->parent == NULL) {
		// ��Ʈ���
		*root = zs; // ���ο� ��Ʈ
		zs->parent = NULL;
	}
	else {
		tree* g = w->parent;
		zs->parent = g;
		if (w->key == g->lChild->key)
			g->lChild = zs;
		else
			g->rChild = zs;
	}

	free(*z);
	free(w);

	return zs;
}

void expandExternal(tree* p) {
	makeTree(&p->lChild, p);
	makeTree(&p->rChild, p);
}