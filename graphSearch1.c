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
		// ���� ����
		scanf("%d %d", &a, &b);
		changeEdge(&G, a, b, &EGidx, n);
	}
	// s��°�� ������ DFS Ž��
	int* visited = (int*)malloc(sizeof(int) * n); // �湮 �������� 0, ������ 1
	for (int i = 0; i < n; i++) // �湮 ���Ѱ����� �ʱ�ȭ
		visited[i] = 0;
	// �湮��� ����
	searching(G, n, s, visited);
	freeNode(G, n);
	return 0;
}

void makeGraph(graph* G, int n, int m) {
	G->VT = (vertices*)malloc(sizeof(vertices) * n); // ���� �迭 ����
	for (int i = 0; i < n; i++) {
		G->VT[i].ele = i + 1; // �� ������
		G->VT[i].incidence = (list*)malloc(sizeof(list)); // �� ������ ����� �������� ������ ���� list
		G->VT[i].incidence->next = NULL; // �ʱ�ȭ
	}
	// ����
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
	} // a�� b ������ �������� ������ ����
	list* p = G->VT[a - 1].incidence->next;
	int e;

	while (p != NULL) {
		e = p->idx;
		if ((G->EG[e].V1 == a && G->EG[e].V2 == b) ||
			(G->EG[e].V1 == b && G->EG[e].V2 == a)) {
			// �̹� �����
			return;
		}
		else {
			if (p == NULL)
				break;
			p = p->next;
		}
		// ���� w �� 0�̸� ����
	}
	if (p == NULL) {
		// ��ã��. ���� �߰��ؾ� �Ѵ�.
		G->EG[*EGidx].V1 = a;
		G->EG[*EGidx].V2 = b;
		// �� ����Ʈ ���� edges����
		connectEdge(G, a, b, EGidx);
		if (a == b) { // �����϶�
			(*EGidx)++; // ���� �ε�����
			return;
		}
		// �ݴ�� ����
		connectEdge(G, b, a, EGidx);
		(*EGidx)++; // ���� �ε�����
	}
}

void connectEdge(graph* G, int a, int b, int* EGidx) {
	// �� ����Ʈ ���� edges����
	list* np1 = (list*)malloc(sizeof(list));
	np1->next = NULL;
	np1->idx = *EGidx;
	list* p = G->VT[a - 1].incidence; // a ��ġ ã��
	while (p != NULL) {
		// ������ ��ġ ����
		if (p->next == NULL) {
			// �������� ����
			p->next = np1;
			break;
		}
		// �������� ����� ���ؼ� ��ġ�� ã�ƾ� �Ѵ�.
		if (G->EG[p->next->idx].V1 == a) {
			// b�� V2�� ���� ������ ��ġ���� Ȯ���Ѵ�.
			if (G->EG[p->next->idx].V2 > b) {
				// ����
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		else if (G->EG[p->next->idx].V2 == a) {
			// b�� V1�� ���� ������ ��ġ���� Ȯ���Ѵ�.
			if (G->EG[p->next->idx].V1 > b) {
				// ����
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		p = p->next; // ��ã������ ��������
	}
}

void searching(graph G, int n, int s, int* visited) {
	// s �湮
	visited[s - 1] = 1;
	printf("%d\n", s);
	list* p = G.VT[s - 1].incidence->next; // Ž��
	while (p != NULL) {
		// ����� ������ Ž��
		int edgeIdx = p->idx; // edges�� ����� ���� ����
		int nextVertex = G.EG[edgeIdx].V1 == s ? G.EG[edgeIdx].V2 : G.EG[edgeIdx].V1; // ����� ���� ã��
		if (visited[nextVertex - 1] == 0) {
			// �湮�� ���� ���ٸ�, 
			searching(G, n, nextVertex, visited); // �湮
		}
		p = p->next; // �������� ����� ���� ����.
	}
}