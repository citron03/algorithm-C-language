#include <stdio.h>
#include <stdlib.h>

// 간선 정보
typedef struct edges {
	int a, b, weight;
}eg;

typedef struct adjacencyList {
	struct adjacencyList* next; // 다음 연결된 정점 정보
	int edgeIdx; // 간선정보 배열의 index
}al;

typedef struct vertices {
	int vertex; // 정점 번호
}vt;

typedef struct Graph {
	vt* vertices; // 정점
	eg* edges; // 간선
}graph;

typedef struct Heap {
	int weight; // 간선 무게
	int edge; // 간선 번호
}Heap;

typedef struct separateSet {
	al* head;
	int size; // 큰쪽으로 합치기 위함
}SS;

void initGraph(graph* G, int n, int m); // 그래프 초기화
void insertEdge(graph G, int a, int b, int w, int i); // 삽입
int KruskalMST(graph G, int n, int m);

// 힙
void bulidHeap(graph G, Heap* heap, int n);
int removeMin(Heap* heap, int i);
void swap(Heap* heap, int idx, int small);
void downHeap(Heap* heap, int idx, int n);
void upHeap(Heap* heap, int idx);

// 분리집합
int findSet(graph G, SS* set, int vertex, int n);
void unionSet(SS* set, int v0, int v1);

int main() {
	graph G;
	// Kruskal 알고리즘
	int n, m;
	int a, b, w;
	scanf("%d %d", &n, &m);
	initGraph(&G, n, m); // 그래프 초기화
	for (int i = 0; i < m; i++) {
		// 간선 정보를 입력받는다.
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(G, a, b, w, i); // 삽입
	}
	printf("%d", KruskalMST(G, n, m));
	// free
	free(G.edges);
	free(G.vertices);
	return 0;
}

void initGraph(graph* G, int n, int m) {
	// 그래프 초기화
	G->vertices = (vt*)malloc(sizeof(vt) * n);
	// 정점 번호
	for (int i = 0; i < n; i++) {
		G->vertices[i].vertex = i + 1;
	}
	// 간선 정보
	G->edges = (eg*)malloc(sizeof(eg) * m);
}

void insertEdge(graph G, int a, int b, int w, int i) {
	// 간선 정보를 삽입한다.
	G.edges[i].a = a;
	G.edges[i].b = b;
	G.edges[i].weight = w; // 가중치
}

void swap(Heap* heap, int idx, int small) {
	// 무게값 바꾼다.
	int tmpD = heap[idx].weight;
	heap[idx].weight = heap[small].weight;
	heap[small].weight = tmpD;
	// 간선 정보를 바꾼다.
	int tmpV = heap[idx].edge;
	heap[idx].edge = heap[small].edge;
	heap[small].edge = tmpV;
}

void downHeap(Heap* heap, int idx, int n) {
	int left = idx * 2, right = idx * 2 + 1;
	if (left > n)
		return;
	int small = left;
	if (right <= n)
		if (heap[right].weight < heap[left].weight) // 거리를 기준으로
			small = right;
	if (heap[idx].weight <= heap[small].weight)
		return;
	swap(heap, idx, small);
	downHeap(heap, small, n); // 재귀
}

void bulidHeap(graph G, Heap* heap, int n) {
	for (int i = n / 2; i >= 1; i--)
		downHeap(heap, i, n); // 힙 만들기
}

int removeMin(Heap* heap, int i) {
	// 최소값 반환
	if (i <= 0)
		return;
	int R = heap[1].edge; // 가장 가벼운 무게
	swap(heap, 1, i); // 바꾼다.
	downHeap(heap, 1, i - 1); // 하나를 빼고 다시 힙속성 복구
	return R; // 최솟값
}

void upHeap(Heap* heap, int idx) {
	if (idx <= 1)
		return;
	if (heap[idx].weight < heap[idx / 2].weight) {
		// 부모노드가 더 클때
		swap(heap, idx, idx / 2);
		upHeap(heap, idx / 2); // 부모노드로 upHeap
	}
}

int findSet(graph G, SS* set, int vertex, int n) {
	// 정점이 들어있는 가방의 번호를 찾아 반환
	al* p = NULL;
	for (int i = 0; i < n; i++) {
		p = set[i].head;
		while (p != NULL) {
			if (G.vertices[p->edgeIdx - 1].vertex == vertex) // 찾음
				return i;
			p = p->next; 
		}
	}
	return -1;
}

void unionSet(SS* set, int v0, int v1) {
	// 집합을 하나로 합친다. 큰쪽으로
	int big, small;
	if (set[v0].size > set[v1].size) {
		big = v0;
		small = v1;
	}
	else {
		big = v1;
		small = v0;
	}
	// 붙이기
	al* p = set[small].head, * q = NULL;
	while (p != NULL) {
		q = p;
		p = p->next;
		// 맨 앞에 붙인다.
		q->next = set[big].head;
		set[big].head = q;
	}
	// 마지막으로 데이터를 정리
	set[small].head = NULL;
	set[big].size += set[small].size;
	set[small].size = 0;
}

int KruskalMST(graph G, int n, int m) {
	int sum = 0; // 총 무게
	int size = m;
	int u, v[2];
	// 간선을 기준으로 한다.
	Heap* PQ = (Heap*)malloc(sizeof(Heap) * (m + 1));
	// 우선순위 큐 초기화
	for (int i = 0; i < m; i++) {
		PQ[i + 1].edge = i + 1;
		PQ[i + 1].weight = G.edges[i].weight;
	}
	// 힙화
	for (int i = m / 2; i >= 1; i--)
		downHeap(PQ, i, m);
	// 집합 (각 정점이 들어있는 가방)
	SS* set = (SS*)malloc(sizeof(SS) * n);
	// 초기화
	for (int i = 0; i < n; i++) {
		set[i].head = (al*)malloc(sizeof(al));
		set[i].head->next = NULL;
		set[i].head->edgeIdx = G.vertices[i].vertex; // 정점 저장
		set[i].size = 1; // 정점 하나
	}
	while (size > 0) { // 간선 갯수만큼 반복
		u = removeMin(PQ, size); // 가장 작은 무게의 간선
		// 가작 작은 무게의 간선이 연결된 각 정점을 담고있는 가방
		v[0] = findSet(G, set, G.edges[u - 1].a, n);
		v[1] = findSet(G, set, G.edges[u - 1].b, n);
		// 만약 두 정점이 다른 가방에 담겨있다면, 하나의 가방으로 합친다.
		if (v[0] != v[1]) {
			sum += G.edges[u - 1].weight; // 합산
			printf("%d ", G.edges[u - 1].weight); // 간선의 무게 출력
			unionSet(set, v[0], v[1]);
		}
		size -= 1;
	}
	printf("\n");
	free(PQ);
	free(set);
	return sum;
}