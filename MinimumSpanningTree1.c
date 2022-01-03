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
	al* adjacent; // ��������Ʈ
}vt;

typedef struct Graph {
	vt* vertices; // ����
	eg* edges; // ����
}graph;
// ���� ������ �ٲ��ָ鼭 �Ÿ��� ������ �ѹ��� �ٲ�� �ϱ⿡ ����ü�� �ѹ��� ����
typedef struct Heap {
	int distance; // �Ÿ�
	int vertex; // ���� ��ȣ
}Heap;

void initGraph(graph* G, int n, int m); // �׷��� �ʱ�ȭ
void insertEdge(graph G, int a, int b, int w, int i); // ����
void connectAl(graph G, int a, int i); // ��������Ʈ�� ���� ���� �߰�
void freeAllList(graph G, int n); // ��������Ʈ free�Ѵ�.
int PrimJarnikMST(graph G, int n, int s); // Prim-Jarnik �˰���
// ��
void bulidHeap(graph G, Heap* heap, int n);
int removeMin(Heap* heap, int i);
void swap(Heap* heap, int idx, int small);
void downHeap(Heap* heap, int idx, int n);
void upHeap(Heap* heap, int idx);
void replaceKey(Heap* heap, int i, int z, int distanceZ);
int includeVertex(Heap* heap, int z, int i);

int main() {
	graph G;
	// Prim-Jarnik �˰���
	int n, m;
	int a, b, w;
	scanf("%d %d", &n, &m);
	initGraph(&G, n, m); // �׷��� �ʱ�ȭ
	for (int i = 0; i < m; i++) {
		// ���� ������ �Է¹޴´�.
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(G, a, b, w, i); // ����
	}
	printf("\n%d", PrimJarnikMST(G, n, 1)); // 1�� ��������
	// free
	free(G.edges);
	freeAllList(G, n);
	free(G.vertices);
	return 0;
}

void initGraph(graph* G, int n, int m) {
	// �׷��� �ʱ�ȭ
	G->vertices = (vt*)malloc(sizeof(vt) * n);
	// ���� ��ȣ
	for (int i = 0; i < n; i++) {
		G->vertices[i].vertex = i + 1;
		// ��������Ʈ�� ��� ���
		G->vertices[i].adjacent = (al*)malloc(sizeof(al));
		G->vertices[i].adjacent->next = NULL;
	}
	// ���� ����
	G->edges = (eg*)malloc(sizeof(eg) * m);
}

void connectAl(graph G, int a, int i) {
	// ������ ������ ��� �ε��� i �߰�
	al* p = G.vertices[a - 1].adjacent;
	al* newAL = (al*)malloc(sizeof(al));
	newAL->edgeIdx = i; // �ε��� ����
	// �� �տ� �߰��Ѵ�.
	newAL->next = p->next;
	p->next = newAL;
}

void insertEdge(graph G, int a, int b, int w, int i) {
	// ���� ������ �����Ѵ�.
	G.edges[i].a = a;
	G.edges[i].b = b;
	G.edges[i].weight = w; // ����ġ
	connectAl(G, a, i);
	connectAl(G, b, i); // �� ������ ���� ���� ����
}

void freeAllList(graph G, int n) {
	// free
	al* p = NULL, * q = NULL;
	for (int i = 0; i < n; i++) {
		p = G.vertices[i].adjacent; // ���� ����
		while (p != NULL) {
			q = p;
			p = p->next; // ��������
			free(q); // ����
		}
	}
}

void swap(Heap* heap, int idx, int small) {
	// �Ÿ��� �ٲ۴�.
	int tmpD = heap[idx].distance;
	heap[idx].distance = heap[small].distance;
	heap[small].distance = tmpD;
	// �������� �ٲ۴�.
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
		if (heap[right].distance < heap[left].distance) // �Ÿ��� ��������
			small = right;
	if (heap[idx].distance <= heap[small].distance)
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
		return -1;
	int R = heap[1].vertex; // ���� ª�� ���� ��ȯ
	swap(heap, 1, i); // �ٲ۴�.
	downHeap(heap, 1, i - 1); // �ϳ��� ���� �ٽ� ���Ӽ� ����
	return R; // �ּڰ�
}

int opposite(graph G, int u, al* e) {
	// �ݴ��� ���� ��ȯ
	if (G.edges[e->edgeIdx].a != u)
		return G.edges[e->edgeIdx].a;
	else
		return G.edges[e->edgeIdx].b;
}

int includeVertex(Heap* heap, int z, int i) {
	// ���� z�� ������ return 1
	for (int idx = 1; idx <= i; idx++)
		if (heap[idx].vertex == z)
			return 1;
	return 0; // ����
}

void upHeap(Heap* heap, int idx) {
	if (idx <= 1)
		return;
	if (heap[idx].distance < heap[idx / 2].distance) {
		// �θ��尡 �� Ŭ��
		swap(heap, idx, idx / 2);
		upHeap(heap, idx / 2); // �θ���� upHeap
	}
}

void replaceKey(Heap* heap, int i, int z, int distanceZ) {
	for (int idx = 1; idx < i; idx++) {
		if (heap[idx].vertex == z) { // ������ ã��
			heap[idx].distance = distanceZ; // �Ÿ� ����
			upHeap(heap, idx); // �ٲ� ���� �������� upHeap�ؼ� �ڸ��� ã�´�.
			return; // ��ü�� ������.
		}
	}
}

int PrimJarnikMST(graph G, int n, int s) {
	Heap* heap = (Heap*)malloc(sizeof(Heap) * (n + 1)); // �Ÿ�, Heap. ���� �湮 ���� ������
	int* distance = (int*)malloc(sizeof(int) * (n + 1)); // �賶���� ������ �湮�ϴ� �� �ɸ��� �Ÿ�
	for (int i = 1; i <= n; i++) {
		heap[i].vertex = i; // ���� ��ȣ
		heap[i].distance = 10000; // MAX
		distance[i] = 10000; // ���Ѵ�
	}
	distance[s] = 0;
	heap[s].distance = 0; // �ʱ�ȭ
	// �켱���� ť, �� ���
	bulidHeap(G, heap, n);
	// ���� �������� �ݺ�
	int i = n;
	int sum = 0; // MST �ѹ���
	while (i > 0) {
		// ��� �������� ���� u�� �����ϴ����� ������� �ʴ´�. �賶�ȿ��� ���� u�� �����ϴ� ������ ����.
		int u = removeMin(heap, i); // ���� ��ȣ�� ��ȯ. �Ÿ��� X, ���� distance�� ���� �Ÿ��� �˾Ƴ���.
		printf(" %d", G.vertices[u - 1].vertex); // MST ������ �߰��Ǵ� ����
		sum += distance[u]; // ���� �Ÿ� ����
		al* e = G.vertices[u - 1].adjacent->next; // ���� ���� ����
		while (e != NULL) {
			int z = opposite(G, u, e); // �ݴ����� ���۵Ǵ� ����
			if (includeVertex(heap, z, i) && // ���� z�� heap�� ����, �� ���� �湮 ����
				G.edges[e->edgeIdx].weight < distance[z]) { // �賶���� ������ �湮�ϴ� �� �� ª�� ���� �߰�
				distance[z] = G.edges[e->edgeIdx].weight; // �Ÿ� ����
				replaceKey(heap, i, z, distance[z]); // �Ÿ� �� ��ü
			}
			e = e->next; // ���� ���� ���� üũ
		}
		i--; // ���� �湮����
	}
	// free
	free(heap);
	free(distance);
	return sum;
}