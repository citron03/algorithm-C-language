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
	al* adjacent; // 인접리스트
}vt;

typedef struct Graph {
	vt* vertices; // 정점
	eg* edges; // 간선
}graph;
// 힙의 정보를 바꿔주면서 거리와 정점을 한번에 바꿔야 하기에 구조체로 한번에 설정
typedef struct Heap {
	int distance; // 거리
	int vertex; // 정점 번호
}Heap;

void initGraph(graph* G, int n, int m); // 그래프 초기화
void insertEdge(graph G, int a, int b, int w, int i); // 삽입
void connectAl(graph G, int a, int i); // 인접리스트에 간선 정보 추가
void freeAllList(graph G, int n); // 인접리스트 free한다.
int PrimJarnikMST(graph G, int n, int s); // Prim-Jarnik 알고리즘
// 힙
void bulidHeap(graph G, Heap* heap, int n);
int removeMin(Heap* heap, int i);
void swap(Heap* heap, int idx, int small);
void downHeap(Heap* heap, int idx, int n);
void upHeap(Heap* heap, int idx);
void replaceKey(Heap* heap, int i, int z, int distanceZ);
int includeVertex(Heap* heap, int z, int i);

int main() {
	graph G;
	// Prim-Jarnik 알고리즘
	int n, m;
	int a, b, w;
	scanf("%d %d", &n, &m);
	initGraph(&G, n, m); // 그래프 초기화
	for (int i = 0; i < m; i++) {
		// 간선 정보를 입력받는다.
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(G, a, b, w, i); // 삽입
	}
	printf("\n%d", PrimJarnikMST(G, n, 1)); // 1번 정점으로
	// free
	free(G.edges);
	freeAllList(G, n);
	free(G.vertices);
	return 0;
}

void initGraph(graph* G, int n, int m) {
	// 그래프 초기화
	G->vertices = (vt*)malloc(sizeof(vt) * n);
	// 정점 번호
	for (int i = 0; i < n; i++) {
		G->vertices[i].vertex = i + 1;
		// 인접리스트의 헤드 노드
		G->vertices[i].adjacent = (al*)malloc(sizeof(al));
		G->vertices[i].adjacent->next = NULL;
	}
	// 간선 정보
	G->edges = (eg*)malloc(sizeof(eg) * m);
}

void connectAl(graph G, int a, int i) {
	// 간선의 정보가 담긴 인덱스 i 추가
	al* p = G.vertices[a - 1].adjacent;
	al* newAL = (al*)malloc(sizeof(al));
	newAL->edgeIdx = i; // 인덱스 정보
	// 맨 앞에 추가한다.
	newAL->next = p->next;
	p->next = newAL;
}

void insertEdge(graph G, int a, int b, int w, int i) {
	// 간선 정보를 삽입한다.
	G.edges[i].a = a;
	G.edges[i].b = b;
	G.edges[i].weight = w; // 가중치
	connectAl(G, a, i);
	connectAl(G, b, i); // 두 정점에 간선 정보 저장
}

void freeAllList(graph G, int n) {
	// free
	al* p = NULL, * q = NULL;
	for (int i = 0; i < n; i++) {
		p = G.vertices[i].adjacent; // 해제 시작
		while (p != NULL) {
			q = p;
			p = p->next; // 다음으로
			free(q); // 해제
		}
	}
}

void swap(Heap* heap, int idx, int small) {
	// 거리값 바꾼다.
	int tmpD = heap[idx].distance;
	heap[idx].distance = heap[small].distance;
	heap[small].distance = tmpD;
	// 정점값을 바꾼다.
	int tmpV = heap[idx].vertex;
	heap[idx].vertex = heap[small].vertex;
	heap[small].vertex = tmpV;
}

void downHeap(Heap* heap, int idx, int n) {
	int left = idx * 2, right = idx * 2 + 1;
	if (left > n)
		return;
	int small = left;
	if (right <= n)
		if (heap[right].distance < heap[left].distance) // 거리를 기준으로
			small = right;
	if (heap[idx].distance <= heap[small].distance)
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
		return -1;
	int R = heap[1].vertex; // 가장 짧은 정점 반환
	swap(heap, 1, i); // 바꾼다.
	downHeap(heap, 1, i - 1); // 하나를 빼고 다시 힙속성 복구
	return R; // 최솟값
}

int opposite(graph G, int u, al* e) {
	// 반대편 정점 반환
	if (G.edges[e->edgeIdx].a != u)
		return G.edges[e->edgeIdx].a;
	else
		return G.edges[e->edgeIdx].b;
}

int includeVertex(Heap* heap, int z, int i) {
	// 정점 z를 가지면 return 1
	for (int idx = 1; idx <= i; idx++)
		if (heap[idx].vertex == z)
			return 1;
	return 0; // 없음
}

void upHeap(Heap* heap, int idx) {
	if (idx <= 1)
		return;
	if (heap[idx].distance < heap[idx / 2].distance) {
		// 부모노드가 더 클때
		swap(heap, idx, idx / 2);
		upHeap(heap, idx / 2); // 부모노드로 upHeap
	}
}

void replaceKey(Heap* heap, int i, int z, int distanceZ) {
	for (int idx = 1; idx < i; idx++) {
		if (heap[idx].vertex == z) { // 정점을 찾아
			heap[idx].distance = distanceZ; // 거리 갱신
			upHeap(heap, idx); // 바뀐 값을 기준으로 upHeap해서 자리를 찾는다.
			return; // 교체를 끝낸다.
		}
	}
}

int PrimJarnikMST(graph G, int n, int s) {
	Heap* heap = (Heap*)malloc(sizeof(Heap) * (n + 1)); // 거리, Heap. 아직 방문 안한 정점들
	int* distance = (int*)malloc(sizeof(int) * (n + 1)); // 배낭에서 정점을 방문하는 데 걸리는 거리
	for (int i = 1; i <= n; i++) {
		heap[i].vertex = i; // 정점 번호
		heap[i].distance = 10000; // MAX
		distance[i] = 10000; // 무한대
	}
	distance[s] = 0;
	heap[s].distance = 0; // 초기화
	// 우선순위 큐, 힙 사용
	bulidHeap(G, heap, n);
	// 힙이 빌때까지 반복
	int i = n;
	int sum = 0; // MST 총무게
	while (i > 0) {
		// 어느 정점에서 정점 u에 도달하는지는 고려하지 않는다. 배낭안에서 정점 u에 도달하는 것으로 본다.
		int u = removeMin(heap, i); // 정점 번호를 반환. 거리는 X, 따라서 distance를 보고 거리를 알아낸다.
		printf(" %d", G.vertices[u - 1].vertex); // MST 생성시 추가되는 정점
		sum += distance[u]; // 계산된 거리 저장
		al* e = G.vertices[u - 1].adjacent->next; // 인접 정점 조사
		while (e != NULL) {
			int z = opposite(G, u, e); // 반대편에서 시작되는 정점
			if (includeVertex(heap, z, i) && // 정점 z가 heap에 존재, 즉 아직 방문 안함
				G.edges[e->edgeIdx].weight < distance[z]) { // 배낭에서 정점을 방문하는 데 더 짧은 길을 발견
				distance[z] = G.edges[e->edgeIdx].weight; // 거리 갱신
				replaceKey(heap, i, z, distance[z]); // 거리 값 교체
			}
			e = e->next; // 다음 연결 정점 체크
		}
		i--; // 다음 방문으로
	}
	// free
	free(heap);
	free(distance);
	return sum;
}