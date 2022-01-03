#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {

	struct Tree* left, * right;
	int elem;

}Tree;

void insert(Tree** root, int parent, int left, int right);
void find(Tree* root, int parent, Tree** findP);
void freeTree(Tree* root);
Tree* makeTree(int e);
void printTree(char search[], Tree* root);

int main() {

	Tree* root = NULL;

	int n1, n2;
	int parent, left, right;
	char search[101];

	scanf("%d", &n1);


	for (int i = 0; i < n1; i++) {
		scanf("%d %d %d", &parent, &left, &right);
		insert(&root, parent, left, right);
	}

	scanf("%d", &n2);
	getchar();

	for (int i = 0; i < n2; i++) {
		gets(search);
		Tree* q = root;

		printTree(search, q);

	}

	freeTree(root);

	return 0;
}

void insert(Tree** root, int parent, int left, int right) {

	// rootÀÏ¶§
	if (*root == NULL) {

		// root
		*root = makeTree(parent);

		// left
		(*root)->left = makeTree(left);

		// right
		(*root)->right = makeTree(right);
	}
	else {
		// find
		Tree* p = NULL;
		find(*root, parent, &p);

		p->left = makeTree(left);


		p->right = makeTree(right);

	}


}

void find(Tree* root, int parent, Tree** findP) {


	if (root->elem == parent) {
		*findP = root;
		return;
	}
	else {
		if (root->left != NULL)
			find(root->left, parent, findP);
		if (root->right != NULL)
			find(root->right, parent, findP);
	}

}

void freeTree(Tree* root) {

	if (root->left != NULL)
		freeTree(root->left);
	else if (root->right != NULL)
		freeTree(root->right);
	free(root);
}

Tree* makeTree(int e) {

	Tree* p = NULL;

	p = (Tree*)malloc(sizeof(Tree));
	p->elem = e;
	p->right = NULL;
	p->left = NULL;


	return p;
}

void printTree(char search[], Tree* root) {


	printf("%d ", root->elem);

	for (int j = 0; j < strlen(search); j++) {
		if (search[j] == 'L') {
			root = root->left;
		}
		else {
			root = root->right;
		}
		printf("%d ", root->elem);
	}

	printf("\n");

}