#include <stdio.h>
#include <stdlib.h>

//  키들은 중복이 없는 1 이상의 정수로 전제한다. 즉, 중복 키 검사는 불필요하다

// 부모 노드의 포인터를 갖는 트리 구조
typedef struct Tree {
	struct Tree* left, * right, * parent;
	int ele;
}tree;

// 힙 정렬 함수
void downHeap(tree* p);
void swapElement(tree* p1, tree* p2);
void rBuildHeap(tree* p);

// 이진트리 관련 함수
tree* getNode(tree* p);
void advanceLast(tree** p);
void insertKey(tree* p, int num);
void freeTree(tree *p);

// 레벨 순회를 위한 함수들 (큐 함수 포함)
void printheap(tree* p);
void enqueue(tree** p, int* idx, tree* node);
tree* dequeue(tree** p, int* idx);

int main() {

	// 변수 관리
	int n, num;
	tree* p = NULL, * lastNode;
	scanf("%d", &n); // 입력받을 크기

	p = getNode(NULL); // 루트노드는 부모노드가 NULL
	scanf("%d", &num); // key 값
	insertKey(p, num); // key값을 삽입하고 왼쪽, 오른쪽 노드를 만듦

	lastNode = p; // 마지막 노드의 위치
	for (int i = 1; i < n; i++) {
		advanceLast(&lastNode); // 삽입 위치 찾기
		scanf("%d", &num); // key 값
		insertKey(lastNode, num); // key값을 삽입하고 왼쪽, 오른쪽 노드를 만듦
	}
	rBuildHeap(p); // 힙정렬
	printheap(p); // 출력한다 
	freeTree(p); // 할당 해제
	return 0;
}

tree* getNode(tree* p) {
	// 노드를 생성한다.
	int n;
	tree* R = (tree*)malloc(sizeof(tree));

	R->right = NULL;
	R->left = NULL;
	R->parent = p; // 부모노드 설정
	R->ele = -1; // 외부노드는 비어있는데, 이를 명시한다.

	return R;
}

// 마지막 노드를 기준으로 다음 삽입될 노드의 위치를 찾는다.
void advanceLast(tree** p) {
	while ((*p)->parent != NULL && (*p)->parent->right->ele == (*p)->ele) {
		// 현재 노드가 오른쪽 자식인 동안, 부모 노드로 이동
		*p = (*p)->parent;
	}
	if ((*p)->parent != NULL && (*p)->parent->left->ele == (*p)->ele) {
		// 현재 노드가 왼쪽 자식이면, 형제 노드로 이동
		*p = (*p)->parent->right;
	}
	while ((*p)->left != NULL && (*p)->right != NULL) { // 외부노드에 도달할 때 까지
		// 현재 노드가 내부노드인 동안, 왼쪽 자식으로 이동
		*p = (*p)->left;
	}
}

void insertKey(tree* p, int num) {

	p->ele = num;
	p->left = getNode(p); // 노드를 만든다.
	p->right = getNode(p); // 하지만, 값을 -1로 하여 외부의 빈 노드임을 명시한다.

}

void freeTree(tree* p) {
	// 할당을 해제한다.
	if (p->left != NULL)
		freeTree(p->left);
	if (p->right != NULL)
		freeTree(p->right);
	free(p); // 왼쪽과 오른쪽 노드들을 모두 살핀 후에 free
}


void rBuildHeap(tree* p) {
	// 재귀를 통해서 상향식으로 힙을 구현한다.
	if(p->left->ele != -1) // 외부노드가 아닐때 재귀
		rBuildHeap(p->left);
	if(p->right->ele != -1)
		rBuildHeap(p->right);
	// 위치를 조정한다.
	downHeap(p);
}

void swapElement(tree* p1, tree* p2) {
	// 두 값을 바꿔준다.
	int tmp = p1->ele;
	p1->ele = p2->ele;
	p2->ele = tmp;
}

void downHeap(tree* p) {

	tree* next = NULL;

	if (p->left->ele != -1 && p->right->ele != -1) {
		// 양쪽 다 노드가 존재
		if (p->left->ele > p->right->ele) // 왼쪽이 클 때
			next = p->left; 
		else // 오른쪽이 클 때
			next = p->right;
	}
	else if (p->left->ele != -1) {
		// 왼쪽만 노드가 존재
		next = p->left;
	}
		

	if (next == NULL) // swap 알고리즘과 더 이상의 재귀는 필요없다.
		return;
	else if (next->ele < p->ele) // 이미 최대힙이면 return
		return;
	else {
		swapElement(p, next); // 값 바꾸기
		downHeap(next); // 바꾼 값으로 downheap을 계속해 힙의 조건을 맞춰준다.
	}
}

void printheap(tree* p) {
	// 큐, 노드를 저장한다.
	tree** queue = (tree**)malloc(sizeof(tree*) * 100);
	// index
	int front = 0, rear = 0; //  앞과 뒤
	enqueue(queue, &rear, p); // 루트노드를 큐에 삽입한다.
	// 큐가 비는 순간까지 반복한다.
	while (front != rear) {
		tree* now = dequeue(queue, &front); // 현재 방문한 위치
		printf(" %d", now->ele); // 방문
		// 왼쪽 자식이 있으면 큐에 삽입한다.
		if (now->left->ele != -1)
			enqueue(queue, &rear, now->left);
		// 오른쪽 자식이 있으면 큐에 삽입한다.
		if (now->right->ele != -1) 
			enqueue(queue, &rear, now->right);
	}
	free(queue);
}

void enqueue(tree** p, int* idx, tree* node){
	p[*idx] = node; // 값을 주입한다.
	*idx += 1; // 다음 인덱스로
}

tree* dequeue(tree** p, int* idx) {
	tree* R = p[*idx]; // 값 저장
	p[*idx] = NULL; // 비우기
	*idx += 1; // 인덱스 전진
	return R;
}