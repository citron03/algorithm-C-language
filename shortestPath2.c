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
	// 방향 가중그래프에서 최단거리 찾기
	G graph;
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	// 초기화
	graph.vertices = (vt*)malloc(sizeof(vt) * n);
	graph.edges = (eg*)malloc(sizeof(eg) * m);
	// 정점 초기화
	for (int i = 0; i < n; i++) {
		graph.vertices[i].vertex = i + 1;
		graph.vertices[i].head = (al*)malloc(sizeof(al));
		graph.vertices[i].head->next = NULL;
	}
	// 간선 입력
	int ori, dest, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &ori, &dest, &w);
		insertEdges(graph, ori, dest, w, i);
	}
	BellmanFordShortestPaths(graph, s, n, m); // 최단경로
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
	// 정점 정보 저장
	graph.edges[i].destination = dest;
	graph.edges[i].origin = ori;
	graph.edges[i].weight = w;
	// 간선 정보, 정점에 저장
	al* newest = (al*)malloc(sizeof(al));
	newest->idxEG = i; // 인덱스 저장
	// 맨 앞에 저장한다.
	newest->next = graph.vertices[ori - 1].head->next;
	graph.vertices[ori - 1].head->next = newest;
}

void BellmanFordShortestPaths(G graph, int s, int n, int m) {
	int* distance = (int*)malloc(sizeof(int) * n); // 거리
	for (int i = 0; i < n; i++)
		distance[i] = 30000;
	distance[s - 1] = 0; // 출발지
	// 거리 조정
	int u, z;
	for (int j = 1; j < n - 1; j++) {
		// n-1번 반복한다.
		for (int i = 0; i < m; i++) { // 순서대로 모든 간선 완화작업
			u = graph.edges[i].origin;
			z = graph.edges[i].destination;
			if(distance[z - 1] > distance[u - 1] + graph.edges[i].weight
				&& distance[u - 1] != 30000) // z-1의 거리가 30000이고 u-1의 거리가 30000이면서 간선 무게가 음수이면 잘못된 갱신이 일어난다.
				distance[z - 1] = graph.edges[i].weight + distance[u - 1]; // 갱신
		}
	}
	for (int i = 0; i < n; i++)
		if (distance[i] != 30000 && s - 1 != i) // 방문 안한 정점과 처음 시작한 정점은 출력 X
			printf("%d %d\n", i + 1, distance[i]);
	free(distance);
}