#include <stdio.h>
#include <stdlib.h>

// �Լ� ������ ���Ǳ� ���ؼ� ���� ����� �ʿ䰡 �ִ�.
typedef struct tree {
	struct tree* parent, * lChild, * rChild;
	int key, height;
}tree;

int findElement(int k, tree* root);
void insertItem(int k, tree** root);
tree* treeSearch(int k, tree* root);
int isExternal(tree* w);
int isInternal(tree* w);
tree* inOrderSucc(tree* w); // ��� w�� ������ȸ �İ��ڸ� ��ȯ
void printTree(tree* root);
void expandExternal(tree* p);

void makeTree(tree** p, tree* parent);
void freeTree(tree* p);

void searchAndFixAfterInsertion(tree* p, tree** root);
tree* restructure(tree* x, tree* y, tree* z, tree** root);
int updateHeight(tree* p);
int isBalanced(tree* p);

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
			insertItem(k, &root);
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

void insertItem(int k, tree** root) {
	// Ű ���� �� Ʈ���� �ұ����� �߻����� ���, ����(restructure)�� ����
	tree* w = treeSearch(k, *root); // k�� ���� ����� ���� �ܺ� ���� �̵��Ѵ�.
	if (isInternal(w))
		return;
	else {
		w->key = k;
		expandExternal(w); // �ܺγ��� Ȯ��
		searchAndFixAfterInsertion(w, root); // AVLƮ���� �����.
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

void expandExternal(tree* p) {
	makeTree(&p->lChild, p);
	makeTree(&p->rChild, p);
	
	// ���̸� �������ش�.
	p->lChild->height = 0;
	p->rChild->height = 0;
	p->height = 1;
}

void searchAndFixAfterInsertion(tree* p, tree** root) {
	// �ұ����� ã�Ƽ� ����

	tree* x = NULL, * y = NULL, * z = NULL;

	p->lChild->height = 0;
	p->rChild->height = 0;
	p->height = 1;

	if (p->parent == NULL) // ��Ʈ ���� ����
		return;

	z = p->parent;

	// ��Ʈ��尡 �ƴҶ�
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return; // �θ� ����̸� ����
		z = z->parent; // ���� �ö󰡸� ���̸� ���
	}

	
	if (isBalanced(z)) // ������������ ��
		return;

	//  z�� ���� �ڽ��� y
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;
	//  y�� ���� �ڽ��� x
	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;
	restructure(x, y, z, root);
	/* ���� ��, ���� b�� ��Ʈ�� �ϴ� ��Ʈ���� ��� ���� ������ �����Ѵ�.
	���̱��� �Ӽ��� ��� x, y, z���� ���������γ� ���������γ� ��� �����ȴ� */
}

tree* restructure(tree* x, tree* y, tree* z, tree** root) {
	// ����
	tree* a, *b, *c; // x, y, z�� ������ȸ ����
	tree* T0, * T1, * T2, * T3; //  x, y, z�� ��Ʈ���� ��� x, y,z�� 
	//  ��Ʈ�� �ϴ� ��Ʈ���� ������ 4���� ��Ʈ������ ������ȸ �湮������ ����

	// ���� ��ȸ �湮, a(�����ڽ�) b(��Ʈ) c(�������ڽ�) 
	// 4���� ����� ���� �ִ�.
	if (x->key > y->key && y->key > z->key) {
		// x > y > z
		a = z;
		b = y;
		c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}
	else if (z->key > y->key && y->key > x->key) {
		// z > y > x
		a = x;
		b = y;
		c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
		// ������� ����ȸ��
	}
	else if (y->key > x->key && x->key > z->key) {
		// ������� ����ȸ��
		// y > x > z
		a = z;
		b = x;
		c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else {
		// z > x > y
		a = y;
		b = x;
		c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	if (z->parent == NULL) {
		// z�� ��Ʈ�϶�
		*root = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else {
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	// b�� ����� �� ��Ʈ���� ��ȯ�Ѵ�.
	a->lChild = T0;
	T0->parent = a;
	a->rChild = T1;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	T2->parent = c;
	c->rChild = T3;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	updateHeight(b);


	return b;
}

int updateHeight(tree* p) {

	int h;
	tree* left = NULL, * right = NULL;
	left = p->lChild;
	right = p->rChild;
	h = left->height > right->height ? left->height + 1 : right->height + 1;
	// max �� ��ȯ�� 1�� ���Ѵ�.
	if (h != p->height) {
		p->height = h;
		return 1;
		// ���� �ʴٸ� ����
	}
	else // �ƴϸ� �״��
		return 0;

}

int isBalanced(tree* p) {

	int left = p->lChild->height;
	int right = p->rChild->height;
	int gap = left > right ? left - right : right - left; 
	// AVL Ʈ������ Ȯ��. ���� ���̰� 1�� ������ �ȵ�.
	if (gap > 1)
		return 0;
	else
		return 1;
}
