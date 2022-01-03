#include <stdio.h>
#include <stdlib.h>

typedef struct adjacencyList {
	struct adjacencyList* next;
	int idxEG; 
}al;

typedef struct Vertices {
	int vertex;
	al* head;
}vt;

typedef struct Edges {
	int origin, destination, weight;
}eg;

typedef struct Graph {
	eg* edges;
	vt* vertices;
}G;

void BellmanFordShortestPaths(G graph, int s, int n, int m);
void insertEdges(G graph, int ori, int dest, int w, int i);


int main() {
	// ���� ���߱׷������� �ִܰŸ� ã��
	G graph;
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	// �ʱ�ȭ
	graph.vertices = (vt*)malloc(sizeof(vt) * n);
	graph.edges = (eg*)malloc(sizeof(eg) * m);
	// ���� �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		graph.vertices[i].vertex = i + 1;
		graph.vertices[i].head = (al*)malloc(sizeof(al));
		graph.vertices[i].head->next = NULL;
	}
	// ���� �Է�
	int ori, dest, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &ori, &dest, &w);
		insertEdges(graph, ori, dest, w, i);
	}
	BellmanFordShortestPaths(graph, s, n, m); // �ִܰ��
	// free
	al* p = NULL, * q = NULL;
	for (int i = 0; i < n; i++) {
		al* p = graph.vertices[i].head;
		while (p != NULL) {
			q = p;
			p = p->next;
			free(q);
		}
	}
	free(graph.edges);
	free(graph.vertices);
	return 0;
}

void insertEdges(G graph, int ori, int dest, int w, int i) {
	// ���� ���� ����
	graph.edges[i].destination = dest;
	graph.edges[i].origin = ori;
	graph.edges[i].weight = w;
	// ���� ����, ������ ����
	al* newest = (al*)malloc(sizeof(al));
	newest->idxEG = i; // �ε��� ����
	// �� �տ� �����Ѵ�.
	newest->next = graph.vertices[ori - 1].head->next;
	graph.vertices[ori - 1].head->next = newest;
}

void BellmanFordShortestPaths(G graph, int s, int n, int m) {
	int* distance = (int*)malloc(sizeof(int) * n); // �Ÿ�
	for (int i = 0; i < n; i++)
		distance[i] = 30000;
	distance[s - 1] = 0; // �����
	// �Ÿ� ����
	int u, z;
	for (int j = 1; j < n - 1; j++) {
		// n-1�� �ݺ��Ѵ�.
		for (int i = 0; i < m; i++) { // ������� ��� ���� ��ȭ�۾�
			u = graph.edges[i].origin;
			z = graph.edges[i].destination;
			if(distance[z - 1] > distance[u - 1] + graph.edges[i].weight
				&& distance[u - 1] != 30000) // z-1�� �Ÿ��� 30000�̰� u-1�� �Ÿ��� 30000�̸鼭 ���� ���԰� �����̸� �߸��� ������ �Ͼ��.
				distance[z - 1] = graph.edges[i].weight + distance[u - 1]; // ����
		}
	}
	for (int i = 0; i < n; i++)
		if (distance[i] != 30000 && s - 1 != i) // �湮 ���� ������ ó�� ������ ������ ��� X
			printf("%d %d\n", i + 1, distance[i]);
	free(distance);
}