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
	list* inEdges, * outEdges; // ����, ����
	int inDegree;
}vt;

typedef struct Graph {
	int n, m; // �������� ������ ��
	vt* vertices;
	eg* edges;
}graph;

void initializeGraph(graph* G);
void buildGraph(graph* G);
// ����
void insertVertex(graph* G, char vName, int i);
void insertDirectedEdge(graph* G, char uName, char wName, int i);
int index(graph* G, char vName); // �ε��� ��ȯ
void addFirst(list* H, int i); // H�� ù ��� ��ġ�� ���� i�� ���ҷ� �ϴ� ��带 ����

void topologicalSort(graph* G, int* topSort); 
// G�κ��� ��������� ���ϰų� �������Ŭ�� �������� ����

// ť �Լ�
int isEmpty(int* rear, int* front);
void enqueue(int* Q, int v, int* rear, int* front);
int dequeue(int* Q, int* rear, int* front);

void freeAll(graph G);

int main() {
	int topOrder[100];
	graph G;
	buildGraph(&G); // �Է����κ��� G ����
	topologicalSort(&G, topOrder); // G�� ���� ����
	if (topOrder[0] == 0) // �������Ŭ ����
		printf("0\n");
	else  // �������Ŭ�� ����. 
		for (int i = 1; i <= G.n; i++)
			printf("%c ", G.vertices[topOrder[i]].name);
	freeAll(G); // free
	return 0;
}


void initializeGraph(graph* G) {
	// �����Ҵ�
	G->vertices = (vt*)malloc(sizeof(vt) * 100);
	G->edges = (eg*)malloc(sizeof(eg) * 1000);
}

void buildGraph(graph* G) {
	char vName, uName, wName;
	initializeGraph(G);
	scanf("%d", &G->n);
	for (int i = 0; i < G->n; i++) {
		scanf(" %c", &vName); // ���� �̸�
		insertVertex(G, vName, i);
	}
	scanf("%d", &G->m);
	getchar();
	for (int i = 0; i < G->m; i++) {
		scanf(" %c %c", &uName, &wName); // ���Ⱓ��
		insertDirectedEdge(G, uName, wName, i);
	}
}
// ����
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
	// ���� ����Ʈ�� i ����
	addFirst(G->vertices[u].outEdges, i);
	addFirst(G->vertices[w].inEdges, i);

	G->vertices[w].inDegree += 1; // �������� ����
}

int index(graph* G, char vName) {
	for (int i = 0; i < G->n; i++) {
		if (G->vertices[i].name == vName)
			return i;
	}
}

void addFirst(list* H, int i) {
	// �ʱ�ȭ
	list* node = (list*)malloc(sizeof(list));
	node->edgeIdx = i;
	node->next = H->next;
	H->next = node;
}

void topologicalSort(graph* G, int* topSort) {
	// ť �ʱ�ȭ
	int Q[100], rear = 0, front = 0;
	int in[100]; // ���� i�� ��������
	int t, u, w;
	for (int i = 0; i < G->n; i++) {
		in[i] = G->vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(Q, i, &rear, &front);
	}

	t = 1; // ���� ����

	while (!isEmpty(&rear, &front)) {
		u = dequeue(Q, &rear, &front);
		topSort[t] = u; // ������� t�� ���� u ����
		t = t + 1; // ���� �������
		for (list* e = G->vertices[u].outEdges->next;
			e != NULL; e = e->next) {
			// ��� ���Ⱓ��
			if (e == NULL)
				break;
			w = G->edges[e->edgeIdx].destination;
			in[w] -= 1;
			if (in[w] == 0)
				enqueue(Q, w, &rear, &front);
		}
	}

	if (t <= G->n)
		topSort[0] = 0; // �������Ŭ ����
	else
		topSort[0] = 1;
}

void freeAll(graph G) {
	list* p = NULL, * q = NULL;
	// ����Ʈ�� free
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

// ť �Լ�
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