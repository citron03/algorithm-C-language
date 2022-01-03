#include <stdio.h>
#include <stdlib.h>

typedef struct edges {
	int V1, V2;
}edges;

typedef struct graph {
	int* vertices;
	int** adjacencyMatrix;
	edges* EG;
}graph;

void changeVertex(int a, int b, int n, graph G, int* idxEG);
void searching(graph G, int n, int s, int* visited);
void makeGraph(graph* G, int n, int m);

int main() {
	int n, m, s, a, b, idxEG = 0;
	graph G;
	scanf("%d %d %d", &n, &m, &s);
	// �ʱ�ȭ
	makeGraph(&G, n, m); // �׷��� ����
	for (int i = 0; i < m; i++) {
		// ���� ����
		scanf("%d %d", &a, &b);
		changeVertex(a, b, n, G, &idxEG);
	}
	// s��°�� ������ DFS Ž��
	int* visited = (int*)malloc(sizeof(int) * n); // �湮 �������� 0, ������ 1
	for (int i = 0; i < n; i++) // �湮 ���Ѱ����� �ʱ�ȭ
		visited[i] = 0;
	// �湮��� ����
	searching(G, n, s, visited); // Ž��
	// free
	free(visited);
	for (int i = 0; i < n; i++)
		free(G.adjacencyMatrix[i]);
	free(G.adjacencyMatrix);
	free(G.EG);
	free(G.vertices);
	return 0;
}

void makeGraph(graph* G, int n, int m) {

	G->adjacencyMatrix = (int**)malloc(sizeof(int*) * n);
	G->vertices = (int*)malloc(sizeof(int) * n);
	G->EG = (edges*)malloc(sizeof(edges) * m); // m���� ������
	for (int i = 0; i < n; i++) {
		G->vertices[i] = i + 1; // ����
		G->adjacencyMatrix[i] = (int*)malloc(sizeof(int) * n); // n*n �迭
		for (int j = 0; j < n; j++)
			G->adjacencyMatrix[i][j] = -1; // �ʱ�ȭ
	}
	// �׷��� �������.
}

void changeVertex(int a, int b, int n, graph G, int* idxEG) {
	if (a > n || a < 1 || b > n || b < 1) {
		printf("-1\n");
		return;
	}

	if (G.adjacencyMatrix[a - 1][b - 1] == -1) {
		G.adjacencyMatrix[a - 1][b - 1] = *idxEG;
		G.adjacencyMatrix[b - 1][a - 1] = *idxEG;
		G.EG[*idxEG].V1 = a;
		G.EG[*idxEG].V2 = b;
		(*idxEG)++; // ���� �ε�����
	}
}

void searching(graph G, int n, int s, int* visited) {
	// BFS
	int* p = (int*)malloc(sizeof(int) * n);
	int rear = 0, front = 0;
	// ť�� ù �湮�� ����
	visited[s - 1] = 1;
	p[front] = s;
	front++;
	while (front != rear) {
		int now = p[rear];
		rear = (rear + 1) % n; // ������ ����Ѵ�.
		printf("%d\n", now);
		for (int i = 0; i < n; i++) {
			// �湮 ���������� ����� �ٸ� ���� ã��
			if (visited[i] == 0 && G.adjacencyMatrix[i][now - 1] != -1) {
				p[front] = i + 1; // ť�� �ְ� �����Ѵ�.
				front = (front + 1) % n;
				visited[i] = 1; // �湮
			}
		}
	}
	free(p);
}