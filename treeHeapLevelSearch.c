#include <stdio.h>
#include <stdlib.h>

//  Ű���� �ߺ��� ���� 1 �̻��� ������ �����Ѵ�. ��, �ߺ� Ű �˻�� ���ʿ��ϴ�

// �θ� ����� �����͸� ���� Ʈ�� ����
typedef struct Tree {
	struct Tree* left, * right, * parent;
	int ele;
}tree;

// �� ���� �Լ�
void downHeap(tree* p);
void swapElement(tree* p1, tree* p2);
void rBuildHeap(tree* p);

// ����Ʈ�� ���� �Լ�
tree* getNode(tree* p);
void advanceLast(tree** p);
void insertKey(tree* p, int num);
void freeTree(tree *p);

// ���� ��ȸ�� ���� �Լ��� (ť �Լ� ����)
void printheap(tree* p);
void enqueue(tree** p, int* idx, tree* node);
tree* dequeue(tree** p, int* idx);

int main() {

	// ���� ����
	int n, num;
	tree* p = NULL, * lastNode;
	scanf("%d", &n); // �Է¹��� ũ��

	p = getNode(NULL); // ��Ʈ���� �θ��尡 NULL
	scanf("%d", &num); // key ��
	insertKey(p, num); // key���� �����ϰ� ����, ������ ��带 ����

	lastNode = p; // ������ ����� ��ġ
	for (int i = 1; i < n; i++) {
		advanceLast(&lastNode); // ���� ��ġ ã��
		scanf("%d", &num); // key ��
		insertKey(lastNode, num); // key���� �����ϰ� ����, ������ ��带 ����
	}
	rBuildHeap(p); // ������
	printheap(p); // ����Ѵ� 
	freeTree(p); // �Ҵ� ����
	return 0;
}

tree* getNode(tree* p) {
	// ��带 �����Ѵ�.
	int n;
	tree* R = (tree*)malloc(sizeof(tree));

	R->right = NULL;
	R->left = NULL;
	R->parent = p; // �θ��� ����
	R->ele = -1; // �ܺγ��� ����ִµ�, �̸� ����Ѵ�.

	return R;
}

// ������ ��带 �������� ���� ���Ե� ����� ��ġ�� ã�´�.
void advanceLast(tree** p) {
	while ((*p)->parent != NULL && (*p)->parent->right->ele == (*p)->ele) {
		// ���� ��尡 ������ �ڽ��� ����, �θ� ���� �̵�
		*p = (*p)->parent;
	}
	if ((*p)->parent != NULL && (*p)->parent->left->ele == (*p)->ele) {
		// ���� ��尡 ���� �ڽ��̸�, ���� ���� �̵�
		*p = (*p)->parent->right;
	}
	while ((*p)->left != NULL && (*p)->right != NULL) { // �ܺγ�忡 ������ �� ����
		// ���� ��尡 ���γ���� ����, ���� �ڽ����� �̵�
		*p = (*p)->left;
	}
}

void insertKey(tree* p, int num) {

	p->ele = num;
	p->left = getNode(p); // ��带 �����.
	p->right = getNode(p); // ������, ���� -1�� �Ͽ� �ܺ��� �� ������� ����Ѵ�.

}

void freeTree(tree* p) {
	// �Ҵ��� �����Ѵ�.
	if (p->left != NULL)
		freeTree(p->left);
	if (p->right != NULL)
		freeTree(p->right);
	free(p); // ���ʰ� ������ ������ ��� ���� �Ŀ� free
}


void rBuildHeap(tree* p) {
	// ��͸� ���ؼ� ��������� ���� �����Ѵ�.
	if(p->left->ele != -1) // �ܺγ�尡 �ƴҶ� ���
		rBuildHeap(p->left);
	if(p->right->ele != -1)
		rBuildHeap(p->right);
	// ��ġ�� �����Ѵ�.
	downHeap(p);
}

void swapElement(tree* p1, tree* p2) {
	// �� ���� �ٲ��ش�.
	int tmp = p1->ele;
	p1->ele = p2->ele;
	p2->ele = tmp;
}

void downHeap(tree* p) {

	tree* next = NULL;

	if (p->left->ele != -1 && p->right->ele != -1) {
		// ���� �� ��尡 ����
		if (p->left->ele > p->right->ele) // ������ Ŭ ��
			next = p->left; 
		else // �������� Ŭ ��
			next = p->right;
	}
	else if (p->left->ele != -1) {
		// ���ʸ� ��尡 ����
		next = p->left;
	}
		

	if (next == NULL) // swap �˰���� �� �̻��� ��ʹ� �ʿ����.
		return;
	else if (next->ele < p->ele) // �̹� �ִ����̸� return
		return;
	else {
		swapElement(p, next); // �� �ٲٱ�
		downHeap(next); // �ٲ� ������ downheap�� ����� ���� ������ �����ش�.
	}
}

void printheap(tree* p) {
	// ť, ��带 �����Ѵ�.
	tree** queue = (tree**)malloc(sizeof(tree*) * 100);
	// index
	int front = 0, rear = 0; //  �հ� ��
	enqueue(queue, &rear, p); // ��Ʈ��带 ť�� �����Ѵ�.
	// ť�� ��� �������� �ݺ��Ѵ�.
	while (front != rear) {
		tree* now = dequeue(queue, &front); // ���� �湮�� ��ġ
		printf(" %d", now->ele); // �湮
		// ���� �ڽ��� ������ ť�� �����Ѵ�.
		if (now->left->ele != -1)
			enqueue(queue, &rear, now->left);
		// ������ �ڽ��� ������ ť�� �����Ѵ�.
		if (now->right->ele != -1) 
			enqueue(queue, &rear, now->right);
	}
	free(queue);
}

void enqueue(tree** p, int* idx, tree* node){
	p[*idx] = node; // ���� �����Ѵ�.
	*idx += 1; // ���� �ε�����
}

tree* dequeue(tree** p, int* idx) {
	tree* R = p[*idx]; // �� ����
	p[*idx] = NULL; // ����
	*idx += 1; // �ε��� ����
	return R;
}