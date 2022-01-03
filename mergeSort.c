#include <stdio.h>
#include <stdlib.h>


typedef struct LinkedList {
	struct LinkedList* next;
	int ele;
}LL;

LL* makeNode(int ele);
void printNode(LL* p);
// 합병정렬 함수
LL* mergeSort(LL* p, int n);
LL* merge(LL* L1, LL* L2);
void partition(LL* p,int m, LL** L1, LL** L2);

int main() {

	LL* p = NULL,* last = NULL;
	int n, ele;
	scanf("%d", &n);
	scanf("%d", &ele);
	p = makeNode(ele);
	last = p;
	for (int i = 1; i < n; i++) {
		scanf("%d", &ele);
		last->next = makeNode(ele);
		last = last->next;
	}
	p = mergeSort(p, n);
	printNode(p);

	// free
	last = p;
	while (last != NULL) {
		p = last;
		last = last->next;
		free(p);
	}
	return 0;
}

LL* makeNode(int ele) {
	LL* p = NULL;
	p = (LL*)malloc(sizeof(LL));
	p->next = NULL;
	p->ele = ele;
	return p;
}

void printNode(LL* p) {
	while (p != NULL) {
		printf(" %d", p->ele);
		p = p->next;
	}
	printf("\n");
}



// 합병정렬 함수
LL* mergeSort(LL* p, int n) {

	LL* L1 = NULL, * L2 = NULL;

	if (n > 1 && p != NULL) {
		partition(p, n / 2, &L1, &L2);
		
		L1 = mergeSort(L1, n / 2);
		L2 = mergeSort(L2, (int)((n / 2.0) + 0.5)); // 반올림을 한다.
		p = merge(L1, L2);

	}
	return p;
}

LL* merge(LL* L1, LL* L2) {

	LL* p = NULL;

	if (L1 == NULL)
		return L2;
	if (L2 == NULL)
		return L1;
	
	if (L1->ele < L2->ele) {
		p = L1;
		p->next = merge(L1->next, L2);
	}
	else {
		p = L2;
		p->next = merge(L1, L2->next);
	}

	return p;
}

void partition(LL* p, int m, LL** L1, LL** L2) {
	LL* last = p;
	*L1 = p;

	for (int i = 0; i < m - 1; i++) 
		last = last->next;
	
	*L2 = last->next;
	last->next = NULL; // 연결을 끊어 두 개로 나눈다.

}