#include <stdio.h>
#include <stdlib.h>

// ���� ����
typedef struct edges {
	int a, b, weight;
}eg;

typedef struct adjacencyList {
	struct adjacencyList* next; // ���� ����� ���� ����
	int edgeIdx; // �������� �迭�� index
}al;

typedef struct vertices {
	int vertex; // ���� ��ȣ
}vt;

typedef struct Graph {
	vt* vertices; // ����
	eg* edges; // ����
}graph;

typedef struct Heap {
	int weight; // ���� ����
	int edge; // ���� ��ȣ
}Heap;

typedef struct separateSet {
	al* head;
	int size; // ū������ ��ġ�� ����
}SS;

void initGraph(graph* G, int n, int m); // �׷��� �ʱ�ȭ
void insertEdge(graph G, int a, int b, int w, int i); // ����
int KruskalMST(graph G, int n, int m);

// ��
void bulidHeap(graph G, Heap* heap, int n);
int removeMin(Heap* heap, int i);
void swap(Heap* heap, int idx, int small);
void downHeap(Heap* heap, int idx, int n);
void upHeap(Heap* heap, int idx);

// �и�����
int findSet(graph G, SS* set, int vertex, int n);
void unionSet(SS* set, int v0, int v1);

int main() {
	graph G;
	// Kruskal �˰���
	int n, m;
	int a, b, w;
	scanf("%d %d", &n, &m);
	initGraph(&G, n, m); // �׷��� �ʱ�ȭ
	for (int i = 0; i < m; i++) {
		// ���� ������ �Է¹޴´�.
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(G, a, b, w, i); // ����
	}
	printf("%d", KruskalMST(G, n, m));
	// free
	free(G.edges);
	free(G.vertices);
	return 0;
}

void initGraph(graph* G, int n, int m) {
	// �׷��� �ʱ�ȭ
	G->vertices = (vt*)malloc(sizeof(vt) * n);
	// ���� ��ȣ
	for (int i = 0; i < n; i++) {
		G->vertices[i].vertex = i + 1;
	}
	// ���� ����
	G->edges = (eg*)malloc(sizeof(eg) * m);
}

void insertEdge(graph G, int a, int b, int w, int i) {
	// ���� ������ �����Ѵ�.
	G.edges[i].a = a;
	G.edges[i].b = b;
	G.edges[i].weight = w; // ����ġ
}

void swap(Heap* heap, int idx, int small) {
	// ���԰� �ٲ۴�.
	int tmpD = heap[idx].weight;
	heap[idx].weight = heap[small].weight;
	heap[small].weight = tmpD;
	// ���� ������ �ٲ۴�.
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
		if (heap[right].weight < heap[left].weight) // �Ÿ��� ��������
			small = right;
	if (heap[idx].weight <= heap[small].weight)
		return;
	swap(heap, idx, small);
	downHeap(heap, small, n); // ���
}

void bulidHeap(graph G, Heap* heap, int n) {
	for (int i = n / 2; i >= 1; i--)
		downHeap(heap, i, n); // �� �����
}

int removeMin(Heap* heap, int i) {
	// �ּҰ� ��ȯ
	if (i <= 0)
		return;
	int R = heap[1].edge; // ���� ������ ����
	swap(heap, 1, i); // �ٲ۴�.
	downHeap(heap, 1, i - 1); // �ϳ��� ���� �ٽ� ���Ӽ� ����
	return R; // �ּڰ�
}

void upHeap(Heap* heap, int idx) {
	if (idx <= 1)
		return;
	if (heap[idx].weight < heap[idx / 2].weight) {
		// �θ��尡 �� Ŭ��
		swap(heap, idx, idx / 2);
		upHeap(heap, idx / 2); // �θ���� upHeap
	}
}

int findSet(graph G, SS* set, int vertex, int n) {
	// ������ ����ִ� ������ ��ȣ�� ã�� ��ȯ
	al* p = NULL;
	for (int i = 0; i < n; i++) {
		p = set[i].head;
		while (p != NULL) {
			if (G.vertices[p->edgeIdx - 1].vertex == vertex) // ã��
				return i;
			p = p->next; 
		}
	}
	return -1;
}

void unionSet(SS* set, int v0, int v1) {
	// ������ �ϳ��� ��ģ��. ū������
	int big, small;
	if (set[v0].size > set[v1].size) {
		big = v0;
		small = v1;
	}
	else {
		big = v1;
		small = v0;
	}
	// ���̱�
	al* p = set[small].head, * q = NULL;
	while (p != NULL) {
		q = p;
		p = p->next;
		// �� �տ� ���δ�.
		q->next = set[big].head;
		set[big].head = q;
	}
	// ���������� �����͸� ����
	set[small].head = NULL;
	set[big].size += set[small].size;
	set[small].size = 0;
}

int KruskalMST(graph G, int n, int m) {
	int sum = 0; // �� ����
	int size = m;
	int u, v[2];
	// ������ �������� �Ѵ�.
	Heap* PQ = (Heap*)malloc(sizeof(Heap) * (m + 1));
	// �켱���� ť �ʱ�ȭ
	for (int i = 0; i < m; i++) {
		PQ[i + 1].edge = i + 1;
		PQ[i + 1].weight = G.edges[i].weight;
	}
	// ��ȭ
	for (int i = m / 2; i >= 1; i--)
		downHeap(PQ, i, m);
	// ���� (�� ������ ����ִ� ����)
	SS* set = (SS*)malloc(sizeof(SS) * n);
	// �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		set[i].head = (al*)malloc(sizeof(al));
		set[i].head->next = NULL;
		set[i].head->edgeIdx = G.vertices[i].vertex; // ���� ����
		set[i].size = 1; // ���� �ϳ�
	}
	while (size > 0) { // ���� ������ŭ �ݺ�
		u = removeMin(PQ, size); // ���� ���� ������ ����
		// ���� ���� ������ ������ ����� �� ������ ����ִ� ����
		v[0] = findSet(G, set, G.edges[u - 1].a, n);
		v[1] = findSet(G, set, G.edges[u - 1].b, n);
		// ���� �� ������ �ٸ� ���濡 ����ִٸ�, �ϳ��� �������� ��ģ��.
		if (v[0] != v[1]) {
			sum += G.edges[u - 1].weight; // �ջ�
			printf("%d ", G.edges[u - 1].weight); // ������ ���� ���
			unionSet(set, v[0], v[1]);
		}
		size -= 1;
	}
	printf("\n");
	free(PQ);
	free(set);
	return sum;
}