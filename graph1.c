#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	struct list* next;
	int idx;
}list;

typedef struct edges {
	int V1, V2, E;
}edges;

typedef struct vertices {
	struct list* incidence;
	int ele;
}vertices;

void makeVertices(vertices VT[]);
void printNodeNum(vertices VT[], edges EG[], int a);
void changeEdge(vertices VT[], edges EG[], int a, int b, int w, int* EGidx);
void connectEdge(vertices VT[], edges EG[], int a, int b, int* EGidx);
void freeNode(vertices VT[]);

int main() {
	// 인접리스트 구현
	vertices VT[6];
	edges EG[21];
	//int EGidx = 8;
	int EGidx = 0;
	// 그래프 그리기
	makeVertices(VT);
	changeEdge(VT, EG, 1, 2, 1, &EGidx);
	changeEdge(VT, EG, 1, 3, 1, &EGidx);
	changeEdge(VT, EG, 1, 4, 1, &EGidx);
	changeEdge(VT, EG, 1, 6, 2, &EGidx);
	changeEdge(VT, EG, 2, 3, 1, &EGidx);
	changeEdge(VT, EG, 3, 5, 4, &EGidx);
	changeEdge(VT, EG, 5, 5, 4, &EGidx);
	changeEdge(VT, EG, 6, 5, 3, &EGidx);
	// 입력받기
	char c;
	int a, b, w;
	while (1) {
		scanf("%c", &c);
		switch (c)
		{
		case 'a':
			scanf("%d", &a);
			printNodeNum(VT, EG, a);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			changeEdge(VT, EG, a, b, w, &EGidx);
			break;
		case 'q':
			return 0;
		}
	}
	freeNode(VT);
	return 0;
}

void makeVertices(vertices VT[]) {
	for (int i = 0; i < 6; i++) {
		VT[i].ele = i + 1;
		VT[i].incidence = (list*)malloc(sizeof(list));
		VT[i].incidence->next = NULL; // 초기화
	}
}


void printNodeNum(vertices VT[], edges EG[], int a) {
	if (a > 6 || a < 1) {
		printf("-1\n");
		return;
	}
	list* p = VT[a - 1].incidence->next;
	int e;
	while (p != NULL) {
		e = p->idx;
		// 노드 번호와 가중치 출력
		if (EG[e].V1 == a && EG[e].E != 0) {
			printf(" %d %d", EG[e].V2, EG[e].E);
			p = p->next;
		}
		else if (EG[e].V2 == a && EG[e].E != 0) {
			printf(" %d %d", EG[e].V1, EG[e].E);
			p = p->next;
		}
		else
			p = p->next;
	}
	printf("\n");
}

void changeEdge(vertices VT[], edges EG[], int a, int b, int w, int* EGidx) {
	if (a > 6 || a < 1) {
		printf("-1\n");
		return;
	}
	if (b > 6 || b < 1) {
		printf("-1\n");
		return;
	} // a나 b 정점이 존재하지 않으면 종료
	list* p = VT[a - 1].incidence->next;
	int e;

	while (p != NULL) {
		e = p->idx;
		if ((EG[e].V1 == a && EG[e].V2 == b) ||
			(EG[e].V1 == b && EG[e].V2 == a)) {
			EG[e].E = w;
			return;
		}
		else {
			if (p == NULL)
				break;
			p = p->next;
		}
		// 만약 w 가 0이면 삭제
	}
	if (p == NULL) {
		// 못찾음. 새로 추가해야 한다.
		EG[*EGidx].V1 = a;
		EG[*EGidx].V2 = b;
		EG[*EGidx].E = w;
		// 두 리스트 끝에 edges연결
		connectEdge(VT, EG, a, b, EGidx);
		if (a == b) { // 루프일때
			(*EGidx)++; // 다음 인덱스로
			return;
		}
		// 반대로 연결
		connectEdge(VT, EG, b, a, EGidx);
		(*EGidx)++; // 다음 인덱스로
	}
}

void freeNode(vertices VT[]) {
	list* p = NULL, * q = NULL;
	for (int i = 0; i < 6; i++) {
		p = VT[i].incidence;
		while (p != NULL) {
			q = p;
			p = p->next;
			free(q);
		}
	}
}

void connectEdge(vertices VT[], edges EG[], int a, int b, int* EGidx) {
	// 두 리스트 끝에 edges연결
	list* np1 = (list*)malloc(sizeof(list));
	np1->next = NULL;
	np1->idx = *EGidx;
	list* p = VT[a - 1].incidence; // a 위치 찾기
	while (p != NULL) {
		// 마지막 위치 도달
		if (p->next == NULL) {
			// 다음으로 삽입
			p->next = np1;
			break;
		}
		// 오름차순 출력을 위해서 위치를 찾아야 한다.
		if (EG[p->next->idx].V1 == a) {
			// b와 V2를 비교해 삽입할 위치인지 확인한다.
			if (EG[p->next->idx].V2 > b) {
				// 삽입
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		else if (EG[p->next->idx].V2 == a) {
			// b와 V1를 비교해 삽입할 위치인지 확인한다.
			if (EG[p->next->idx].V1 > b) {
				// 삽입
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		p = p->next; // 못찾았으니 다음으로
	}
}