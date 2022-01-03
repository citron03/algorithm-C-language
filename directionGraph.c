#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	struct incident* next;
	int edgeIdx;
}list;

typedef struct edges {
	int origin, destination;
}eg;

typedef struct vertices {
	char name;
	list* inEdges, * outEdges; // 진입, 진출
	int inDegree;
}vt;

typedef struct Graph {
	int n, m; // 정점수와 간선의 수
	vt* vertices;
	eg* edges;
}graph;

void initializeGraph(graph* G);
void buildGraph(graph* G);
// 삽입
void insertVertex(graph* G, char vName, int i);
void insertDirectedEdge(graph* G, char uName, char wName, int i);
int index(graph* G, char vName); // 인덱스 반환
void addFirst(list* H, int i); // H의 첫 노드 위치에 정수 i를 원소로 하는 노드를 삽입

void topologicalSort(graph* G, int* topSort); 
// G로부터 위상순서를 구하거나 방향싸이클이 존재함을 보고

// 큐 함수
int isEmpty(int* rear, int* front);
void enqueue(int* Q, int v, int* rear, int* front);
int dequeue(int* Q, int* rear, int* front);

void freeAll(graph G);

int main() {
	int topOrder[100];
	graph G;
	buildGraph(&G); // 입력으로부터 G 구축
	topologicalSort(&G, topOrder); // G를 위상 정렬
	if (topOrder[0] == 0) // 방향싸이클 존재
		printf("0\n");
	else  // 방향사이클이 없음. 
		for (int i = 1; i <= G.n; i++)
			printf("%c ", G.vertices[topOrder[i]].name);
	freeAll(G); // free
	return 0;
}


void initializeGraph(graph* G) {
	// 동적할당
	G->vertices = (vt*)malloc(sizeof(vt) * 100);
	G->edges = (eg*)malloc(sizeof(eg) * 1000);
}

void buildGraph(graph* G) {
	char vName, uName, wName;
	initializeGraph(G);
	scanf("%d", &G->n);
	for (int i = 0; i < G->n; i++) {
		scanf(" %c", &vName); // 정점 이름
		insertVertex(G, vName, i);
	}
	scanf("%d", &G->m);
	getchar();
	for (int i = 0; i < G->m; i++) {
		scanf(" %c %c", &uName, &wName); // 방향간선
		insertDirectedEdge(G, uName, wName, i);
	}
}
// 삽입
void insertVertex(graph* G, char vName, int i) {
	G->vertices[i].name = vName;
	G->vertices[i].inEdges = (list*)malloc(sizeof(list));
	G->vertices[i].inEdges->next = NULL;
	G->vertices[i].outEdges = (list*)malloc(sizeof(list));
	G->vertices[i].outEdges->next = NULL;
	G->vertices[i].inDegree = 0;
}

void insertDirectedEdge(graph* G, char uName, char wName, int i) {
	int u = index(G, uName);
	int w = index(G, wName);
	G->edges[i].origin = u;
	G->edges[i].destination = w;
	// 간선 리스트에 i 삽입
	addFirst(G->vertices[u].outEdges, i);
	addFirst(G->vertices[w].inEdges, i);

	G->vertices[w].inDegree += 1; // 진입차수 갱신
}

int index(graph* G, char vName) {
	for (int i = 0; i < G->n; i++) {
		if (G->vertices[i].name == vName)
			return i;
	}
}

void addFirst(list* H, int i) {
	// 초기화
	list* node = (list*)malloc(sizeof(list));
	node->edgeIdx = i;
	node->next = H->next;
	H->next = node;
}

void topologicalSort(graph* G, int* topSort) {
	// 큐 초기화
	int Q[100], rear = 0, front = 0;
	int in[100]; // 정점 i의 진입차수
	int t, u, w;
	for (int i = 0; i < G->n; i++) {
		in[i] = G->vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(Q, i, &rear, &front);
	}

	t = 1; // 위상 순위

	while (!isEmpty(&rear, &front)) {
		u = dequeue(Q, &rear, &front);
		topSort[t] = u; // 위상순위 t의 정점 u 저장
		t = t + 1; // 다음 위상순위
		for (list* e = G->vertices[u].outEdges->next;
			e != NULL; e = e->next) {
			// 모든 진출간선
			if (e == NULL)
				break;
			w = G->edges[e->edgeIdx].destination;
			in[w] -= 1;
			if (in[w] == 0)
				enqueue(Q, w, &rear, &front);
		}
	}

	if (t <= G->n)
		topSort[0] = 0; // 방향사이클 존재
	else
		topSort[0] = 1;
}

void freeAll(graph G) {
	list* p = NULL, * q = NULL;
	// 리스트들 free
	for (int i = 0; i < G.n; i++) {
		q = G.vertices[i].inEdges;
		while (q != NULL) {
			p = q;
			q = q->next;
			free(p);
		}
		q = G.vertices[i].outEdges;
		while (q != NULL) {
			p = q;
			q = q->next;
			free(p);
		}
	}
	free(G.edges);
	free(G.vertices);
}

// 큐 함수
int isEmpty(int* rear, int* front) {
	if (*rear == *front)
		return 1;
	else
		return 0;
}
void enqueue(int* Q, int v, int* rear, int* front) {
	Q[*front] = v;
	(*front) = ((*front) + 1) % 100;
}
int dequeue(int* Q, int* rear, int* front) {
	int R = Q[*rear];
	(*rear) = ((*rear) + 1) % 100;
	return R;
}