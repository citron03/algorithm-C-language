#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	struct list* next;
	int idx;
}list;

typedef struct edges {
	int V1, V2;
}edges;

typedef struct vertices {
	struct list* incidence;
	int ele;
}vertices;

typedef struct graph {
	vertices* VT;
	edges* EG;
}graph;

void makeGraph(graph* G, int n, int m);
void changeEdge(graph* G, int a, int b, int* EGidx, int n);
void connectEdge(graph* G, int a, int b, int* EGidx);
void searching(graph G, int n, int s, int* visited);
void freeNode(graph G, int n);

int main() {
	int n, m, s, a, b, EGidx = 0;
	graph G;
	scanf("%d %d %d", &n, &m, &s);
	makeGraph(&G, n, m);
	for (int i = 0; i < m; i++) {
		// 간선 연결
		scanf("%d %d", &a, &b);
		changeEdge(&G, a, b, &EGidx, n);
	}
	// s번째의 노드부터 DFS 탐색
	int* visited = (int*)malloc(sizeof(int) * n); // 방문 안했으면 0, 했으면 1
	for (int i = 0; i < n; i++) // 방문 안한것으로 초기화
		visited[i] = 0;
	// 방문기록 저장
	searching(G, n, s, visited);
	freeNode(G, n);
	return 0;
}

void makeGraph(graph* G, int n, int m) {
	G->VT = (vertices*)malloc(sizeof(vertices) * n); // 정점 배열 생성
	for (int i = 0; i < n; i++) {
		G->VT[i].ele = i + 1; // 각 정점값
		G->VT[i].incidence = (list*)malloc(sizeof(list)); // 각 정점과 연결된 간선들의 정보를 담을 list
		G->VT[i].incidence->next = NULL; // 초기화
	}
	// 간선
	G->EG = (edges*)malloc(sizeof(edges) * m);
}

void freeNode(graph G, int n) {
	list* p = NULL, * q = NULL;
	for (int i = 0; i < n; i++) {
		p = G.VT[i].incidence;
		while (p != NULL) {
			q = p;
			p = p->next;
			free(q);
		}
	}
}

void changeEdge(graph* G, int a, int b, int* EGidx, int n) {
	if (a > n || a < 1) {
		printf("-1\n");
		return;
	}
	if (b > n || b < 1) {
		printf("-1\n");
		return;
	} // a나 b 정점이 존재하지 않으면 종료
	list* p = G->VT[a - 1].incidence->next;
	int e;

	while (p != NULL) {
		e = p->idx;
		if ((G->EG[e].V1 == a && G->EG[e].V2 == b) ||
			(G->EG[e].V1 == b && G->EG[e].V2 == a)) {
			// 이미 연결됨
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
		G->EG[*EGidx].V1 = a;
		G->EG[*EGidx].V2 = b;
		// 두 리스트 끝에 edges연결
		connectEdge(G, a, b, EGidx);
		if (a == b) { // 루프일때
			(*EGidx)++; // 다음 인덱스로
			return;
		}
		// 반대로 연결
		connectEdge(G, b, a, EGidx);
		(*EGidx)++; // 다음 인덱스로
	}
}

void connectEdge(graph* G, int a, int b, int* EGidx) {
	// 두 리스트 끝에 edges연결
	list* np1 = (list*)malloc(sizeof(list));
	np1->next = NULL;
	np1->idx = *EGidx;
	list* p = G->VT[a - 1].incidence; // a 위치 찾기
	while (p != NULL) {
		// 마지막 위치 도달
		if (p->next == NULL) {
			// 다음으로 삽입
			p->next = np1;
			break;
		}
		// 오름차순 출력을 위해서 위치를 찾아야 한다.
		if (G->EG[p->next->idx].V1 == a) {
			// b와 V2를 비교해 삽입할 위치인지 확인한다.
			if (G->EG[p->next->idx].V2 > b) {
				// 삽입
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		else if (G->EG[p->next->idx].V2 == a) {
			// b와 V1를 비교해 삽입할 위치인지 확인한다.
			if (G->EG[p->next->idx].V1 > b) {
				// 삽입
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		p = p->next; // 못찾았으니 다음으로
	}
}

void searching(graph G, int n, int s, int* visited) {
	// s 방문
	visited[s - 1] = 1;
	printf("%d\n", s);
	list* p = G.VT[s - 1].incidence->next; // 탐색
	while (p != NULL) {
		// 가까운 곳부터 탐색
		int edgeIdx = p->idx; // edges에 저장된 연결 정보
		int nextVertex = G.EG[edgeIdx].V1 == s ? G.EG[edgeIdx].V2 : G.EG[edgeIdx].V1; // 연결된 방향 찾기
		if (visited[nextVertex - 1] == 0) {
			// 방문한 적이 없다면, 
			searching(G, n, nextVertex, visited); // 방문
		}
		p = p->next; // 다음으로 연결된 노드로 간다.
	}
}