#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	struct Node* next;
	int x;
}node;

void insertItem(node** hash, int ele, int M);
int searchItem(node** hash, int ele, int M);
int deleteItem(node** hash, int ele, int M);
void printItem(node** hash, int M);
void freeHash(node** hash, int M);
node* makeNode(int ele);

int main() {
	// �и������ �ؽ����̺�
	int M, ele;
	char c;
	node** hash = NULL;
	scanf("%d", &M);
	hash = (node**)malloc(sizeof(node*) * M); // �迭
	// �迭 �ʱ�ȭ
	for (int i = 0; i < M; i++)
		hash[i] = NULL;
	while (1) {
		scanf("%c", &c);
		switch (c)
		{
		case 'i':
			scanf("%d", &ele);
			insertItem(hash, ele, M);
			break;
		case 's':
			scanf("%d", &ele);
			printf("%d\n", searchItem(hash, ele, M));
			break;
		case 'd':
			scanf("%d", &ele);
			printf("%d\n", deleteItem(hash, ele, M));
			break;
		case 'p':
			printItem(hash, M);
			break;
		case 'e':
			freeHash(hash, M);
			return 0;
		}
	}

	return 0;
}

node* makeNode(int ele) {
	node* p = (node*)malloc(sizeof(node));
	p->x = ele;
	p->next = NULL;
	return p;
}

void insertItem(node** hash, int ele, int M) {
	//  h(x) = x % M
	int idx = ele % M;
	node* p = hash[idx]; // �迭 �ε��� ����
	if (p == NULL) {
		// �ʱ� ��Ȳ
		hash[idx] = makeNode(ele);
	}
	else {
		// �� �տ� �����ؾ� �Ѵ�.
		node* newNode = makeNode(ele);
		newNode->next = hash[idx];
		hash[idx] = newNode;
	}
}

int searchItem(node** hash, int ele, int M) {
	int idx = 0;
	int i = ele % M; // ��ġ �Լ�
	node* p = hash[i];
	while (p != NULL) {
		idx++; // �ش� ����Ʈ���� ��ġ
		if (p->x == ele) // ��ġ�� ã���� ��ȯ
			return idx;
		else 
			p = p->next;
	}
	
	return 0; // ��ã���� 0�� ����
}

int deleteItem(node** hash, int ele, int M) {
	int idx = 0;
	int i = ele % M; // ��ġ �Լ�
	node* p = hash[i];
	node* prev = p;
	while (p != NULL) {
		idx++; // �ش� ����Ʈ������ ��ġ
		if (p->x == ele) {
			if (p == prev) {
				// ù ��� ������
				hash[i] = p->next;
				free(p);
				return idx;
			}
			else {
				// free �� �̾���̱�, �׸� ���ؼ� �� ���� ��带 ����ؾ� �Ѵ�.
				prev->next = p->next;
				free(p);
				return idx;
			}
		}
		else {
			if (p != prev) // ���ʿ��� ����. ó���� ��߳��� �ڷδ� �� ����ȴ�.
				prev = prev->next;
			p = p->next;
		}
	}
	
	return 0;
}

void printItem(node** hash, int M) {
	for (int i = 0; i < M; i++) {
		node* p = hash[i];
		while (p != NULL) {
			printf(" %d", p->x);
			p = p->next;
		}
	}
	printf("\n");
}

void freeHash(node** hash, int M) {
	for (int i = 0; i < M; i++) {
		node* p = hash[i];
		while (p != NULL) {
			node* q = p;
			p = p->next;
			free(q);
		} // ��ͷ� �� �迭�� ��� ��带 �Ҵ� �����Ѵ�.
	}
}


