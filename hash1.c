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
	// 분리연쇄법 해시테이블
	int M, ele;
	char c;
	node** hash = NULL;
	scanf("%d", &M);
	hash = (node**)malloc(sizeof(node*) * M); // 배열
	// 배열 초기화
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
	node* p = hash[idx]; // 배열 인덱스 접근
	if (p == NULL) {
		// 초기 상황
		hash[idx] = makeNode(ele);
	}
	else {
		// 맨 앞에 삽입해야 한다.
		node* newNode = makeNode(ele);
		newNode->next = hash[idx];
		hash[idx] = newNode;
	}
}

int searchItem(node** hash, int ele, int M) {
	int idx = 0;
	int i = ele % M; // 위치 함수
	node* p = hash[i];
	while (p != NULL) {
		idx++; // 해당 리스트에서 위치
		if (p->x == ele) // 위치를 찾으면 반환
			return idx;
		else 
			p = p->next;
	}
	
	return 0; // 못찾으면 0을 리턴
}

int deleteItem(node** hash, int ele, int M) {
	int idx = 0;
	int i = ele % M; // 위치 함수
	node* p = hash[i];
	node* prev = p;
	while (p != NULL) {
		idx++; // 해당 리스트에서의 위치
		if (p->x == ele) {
			if (p == prev) {
				// 첫 노드 삭제시
				hash[i] = p->next;
				free(p);
				return idx;
			}
			else {
				// free 후 이어붙이기, 그를 위해서 그 전의 노드를 기억해야 한다.
				prev->next = p->next;
				free(p);
				return idx;
			}
		}
		else {
			if (p != prev) // 최초에는 같다. 처음만 어긋나면 뒤로는 쭉 실행된다.
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
		} // 재귀로 각 배열의 모든 노드를 할당 해제한다.
	}
}


