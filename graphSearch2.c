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
	// 초기화
	makeGraph(&G, n, m); // 그래프 생성
	for (int i = 0; i < m; i++) {
		// 간선 연결
		scanf("%d %d", &a, &b);
		changeVertex(a, b, n, G, &idxEG);
	}
	// s번째의 노드부터 DFS 탐색
	int* visited = (int*)malloc(sizeof(int) * n); // 방문 안했으면 0, 했으면 1
	for (int i = 0; i < n; i++) // 방문 안한것으로 초기화
		visited[i] = 0;
	// 방문기록 저장
	searching(G, n, s, visited); // 탐색
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
	G->EG = (edges*)malloc(sizeof(edges) * m); // m개의 간선들
	for (int i = 0; i < n; i++) {
		G->vertices[i] = i + 1; // 정점
		G->adjacencyMatrix[i] = (int*)malloc(sizeof(int) * n); // n*n 배열
		for (int j = 0; j < n; j++)
			G->adjacencyMatrix[i][j] = -1; // 초기화
	}
	// 그래프 만들어짐.
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
		(*idxEG)++; // 다음 인덱스로
	}
}

void searching(graph G, int n, int s, int* visited) {
	// BFS
	int* p = (int*)malloc(sizeof(int) * n);
	int rear = 0, front = 0;
	// 큐에 첫 방문지 삽입
	visited[s - 1] = 1;
	p[front] = s;
	front++;
	while (front != rear) {
		int now = p[rear];
		rear = (rear + 1) % n; // 꺼내어 출력한다.
		printf("%d\n", now);
		for (int i = 0; i < n; i++) {
			// 방문 안한정점과 연결된 다른 정점 찾기
			if (visited[i] == 0 && G.adjacencyMatrix[i][now - 1] != -1) {
				p[front] = i + 1; // 큐에 넣고 전진한다.
				front = (front + 1) % n;
				visited[i] = 1; // 방문
			}
		}
	}
	free(p);
}