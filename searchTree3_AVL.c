#include <stdio.h>
#include <stdlib.h>

// 함수 원형에 사용되기 위해서 먼저 선언될 필요가 있다.
typedef struct tree {
	struct tree* parent, * lChild, * rChild;
	int key, height;
}tree;

int findElement(int k, tree* root);
void insertItem(int k, tree** root);
tree* treeSearch(int k, tree* root);
int isExternal(tree* w);
int isInternal(tree* w);
tree* inOrderSucc(tree* w); // 노드 w의 중위순회 후계자를 반환
void printTree(tree* root);
void expandExternal(tree* p);

void makeTree(tree** p, tree* parent);
void freeTree(tree* p);

// 삽입과 삭제
void searchAndFixAfterInsertion(tree* p, tree** root);
tree* restructure(tree* x, tree* y, tree* z, tree** root);
int updateHeight(tree* p);
int isBalanced(tree* p);
void searchAndFixAfterRemoval(tree* p, tree** root);
int removeElement(int k, tree** root);
tree* reduceExternal(tree** z, tree** root);
tree* sibling(tree** w);

int main() {

	char c;
	int k, X;
	tree* root = NULL, * Y = NULL;
	makeTree(&root, NULL); // root의 부모노드는 없다.
	while (1) {
		scanf("%c", &c);
		switch (c)
		{
		case 'i':
			scanf("%d", &k);
			getchar();
			insertItem(k, &root);
			break;
		case 'd':
			scanf("%d", &k);
			getchar();
			int R = removeElement(k, &root);
			if(R != -1) // 삭제할 것이 존재할 경우에만
				printf("%d\n", R);
			break;
		case 's':
			scanf("%d", &k);
			getchar();
			Y = treeSearch(k, root);
			if (!isExternal(Y)) // 외부노드가 아닐때 출력
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
	if (isExternal(root)) { // 찾지 못함.
		printf("X\n");
		return -1;
	}
	else
		return w->key;
}

void insertItem(int k, tree** root) {
	// 키 삽입 후 트리에 불균형이 발생했을 경우, 개조(restructure)를 수행
	tree* w = treeSearch(k, *root); // k와 가장 가까운 값의 외부 노드로 이동한다.
	if (isInternal(w))
		return;
	else {
		w->key = k;
		expandExternal(w); // 외부노드로 확장
		searchAndFixAfterInsertion(w, root); // AVL트리로 만든다.
	}
}

tree* treeSearch(int k, tree* root) {
	if (isExternal(root))
		return root;
	if (k == root->key)
		return root;
	else if (k > root->key) // 더 크면 오른쪽으로 가서 탐색
		return treeSearch(k, root->rChild);
	else // 작으면 왼쪽으로 가서 탐색
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
	w = w->rChild; // 오른쪽 자식 노드
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

	// 높이를 설정해준다.
	p->lChild->height = 0;
	p->rChild->height = 0;
	p->height = 1;
}

void searchAndFixAfterInsertion(tree* p, tree** root) {
	// 불균형을 찾아서 수리

	tree* x = NULL, * y = NULL, * z = NULL;

	p->lChild->height = 0;
	p->rChild->height = 0;
	p->height = 1;

	if (p->parent == NULL) // 루트 노드면 리턴
		return;

	z = p->parent;

	// 루트노드가 아닐때
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return; // 부모 노드이면 리턴
		z = z->parent; // 위로 올라가며 높이를 계산
	}


	if (isBalanced(z)) // 균형잡혔으면 끝
		return;

	//  z의 높은 자식을 y
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;
	//  y의 높은 자식을 x
	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;
	restructure(x, y, z, root);
	/* 수행 후, 이제 b를 루트로 하는 부트리의 모든 노드는 균형을 유지한다.
	높이균형 속성은 노드 x, y, z에서 지역적으로나 전역적으로나 모두 복구된다 */
}

tree* restructure(tree* x, tree* y, tree* z, tree** root) {
	// 개조
	tree* a, * b, * c; // x, y, z의 중위순회 나열
	tree* T0, * T1, * T2, * T3; //  x, y, z의 부트리들 가운데 x, y,z를 
	//  루트로 하는 부트리를 제외한 4개의 부트리들의 중위순회 방문순서의 나열

	// 중위 순회 방문, a(왼쪽자식) b(루트) c(오른쪽자식) 
	// 4개의 경우의 수가 있다.
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
		// 여기까지 단일회전
	}
	else if (y->key > x->key && x->key > z->key) {
		// 여기부터 이중회전
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
		// z가 루트일때
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

	// b를 가운데로 한 부트리를 반환한다.
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
	// max 값 반환후 1을 더한다.
	if (h != p->height) {
		p->height = h;
		return 1;
		// 옳지 않다면 갱신
	}
	else // 아니면 그대로
		return 0;

}

int isBalanced(tree* p) {

	int left = p->lChild->height;
	int right = p->rChild->height;
	int gap = left > right ? left - right : right - left;
	// AVL 트리인지 확인. 높이 차이가 1을 넘으면 안됨.
	if (gap > 1)
		return 0;
	else
		return 1;
}

tree* sibling(tree** z) {
	if ((*z)->parent == NULL)
		return NULL; // 루트노드는 형제노드가 없다.
	if ((*z)->parent->lChild == (*z)) // 파라미터 노드가 왼쪽 노드이면 형제노드인 오른쪽 노드 반환
		return (*z)->parent->rChild;
	else
		return (*z)->parent->lChild;
}

void searchAndFixAfterRemoval(tree* p, tree** root) {

	// 1. w에서 T의 루트로 향해 올라가다가 처음 만나는 불균형 노드를 z이라 하자, 그러한 z이 없다면 return
	tree* z = p;
	while (updateHeight(z) && isBalanced(z)) { // 재귀를 돌기에 높이 업데이트 필요하다.
		if (z == *root)
			return;
		z = z->parent;
	}
	if (isBalanced(z)) // 부모노드일때 고려
		return;
	// 2. z의 높은 자식을 y라 하자. 수행 후, y는 w의 조상이 아닌 z의 자식이 되는 것에 유의
	tree* y = z->rChild->height > z->lChild->height ? z->rChild : z->lChild;
	// 3. 다음과 같이 하여 y의 자식 중 하나를 x라 하자.y의 두 자식 중 어느 한쪽이 높으면 높은 자식을 x라 하고, 
	// 두 자식의 높이가 같으면 둘 중 y와 같은 쪽의	자식을 x로 선택
	tree* x = NULL;
	if (y->lChild->height == y->rChild->height) {
		// 같으면 y와 같은 방향으로
		if (y->parent->lChild == y)
			x = y->lChild;
		else
			x = y->rChild;
	}
	else if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;
	// 4. b restructure(x, y, z)
	tree* fix = restructure(x, y, z, root);
	// 5. T를 b의 부모부터 루트까지 올라가면서 균형을 잃은 노드를 찾아 수리하는 것을 계속.
	if (fix == *root)
		return;
	searchAndFixAfterRemoval(fix->parent, root);
}

tree* reduceExternal(tree** z, tree** root) {
	tree* w = (*z)->parent;
	tree* zs = sibling(z);
	if (w->parent == NULL) {
		// 루트노드
		*root = zs; // 새로운 루트
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

int removeElement(int k, tree** root) {
	tree* w = treeSearch(k, *root); // 삭제 위치 찾는다.
	if (isExternal(w)) {
		printf("X\n");
		return -1;
	}
	int e = w->key;
	tree* z = w->lChild;
	tree* zs = NULL;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))
		zs = reduceExternal(&z, root); // root의 위치를 재조정해야할 수도 있음
	else {
		tree* y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key; // 계승한다.
		zs = reduceExternal(&z, root);
	}
	searchAndFixAfterRemoval(zs->parent, root); // 삭제 후 불균형 노드 수리
	return e;
}