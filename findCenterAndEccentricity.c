#include <stdio.h>
#include <stdlib.h>

typedef struct Edges {
	struct Edges* next; // 연결된 다른 정점, 없으면 NULL
	int adVt; // adjacent vertices, 연결된 정점
}edge;

typedef struct Graph {
	// 그래프, 간단버전. 인접리스트
	int verticesNum; // 정점 번호
	edge* adjacent; // 정점과 연결된 다른 정점들의 리스트
}Graph;

void makeVertices(Graph* graph, int n); // 기본설정, 초기화
void initGraph(Graph* graph, int m); // 간선을 입력받아 넣는다.
void freeEdges(Graph* graph, int n); // 간선 정보를 free
void insertEdge(Graph* graph, int a); // 간선 정보 삽입
int isTree(Graph* graph, int n); // 트리인지 검사
void dfs(Graph* graph, int n, int a, int* visited, int prev, int* isCycle); // dfs로 트리인지 검사한다.
void findCenter(Graph* graph, int n); // 중심을 구한다.
int numberOfActive(int* inActice, int n); // 중심을 구하는데 남은 정점의 갯수들
int findConnectionElement(Graph* graph, int n); // 그래프의 연결요소 개수를 반환한다.
void dfsOnlyChck(Graph* graph, int n, int a, int* visited); // 연결요소 찾기 위한 dfs
int isAllVisited(int* visited, int n);

int main() {
	int n, m;
	Graph* graph = NULL;
	scanf("%d %d", &n, &m); // 정점 갯수와 간선 갯수를 입력받는다.
	graph = (Graph*)malloc(sizeof(Graph) * n);
	makeVertices(graph, n); // 그래프 초기화
	initGraph(graph, m); // 간선 연결
	//  G가 트리인지 아닌지 검사
	if (isTree(graph, n)) // 트리라면, 중심 출력. 두 개면 작은 숫자 먼저.
		findCenter(graph, n);
	else // 트리가 아니면, 그래프를 구성하는 연결요소의 개수를 출력한다.
		printf("%d", findConnectionElement(graph, n));
	// free
	freeEdges(graph, n);
	free(graph);
	return 0;
}

void makeVertices(Graph* graph, int n) {
	for (int i = 1; i <= n; i++) {
		graph[i - 1].verticesNum = i; // 정점 번호
		graph[i - 1].adjacent = (edge*)malloc(sizeof(edge)); // 헤더 노드
		graph[i - 1].adjacent->next = NULL;
	}
}

void insertEdge(Graph* graph, int a) {
	// 삽입할 간선 리스트 만들기
	edge* p = (edge*)malloc(sizeof(edge));
	p->adVt = a;
	// 맨 앞에 삽입한다.
	p->next = graph->adjacent->next;
	graph->adjacent->next = p;
}

void initGraph(Graph* graph, int m) {
	int a, b;
	for (int i = 0; i < m; i++) { // m개의 간선 추가
		scanf("%d %d", &a, &b);
		// 각 정점에 연결된 간선 정보를 저장한다.
		insertEdge(&graph[a - 1], b);
		insertEdge(&graph[b - 1], a);
	}
}

void freeEdges(Graph* graph, int n) {
	edge* q = NULL, * p = NULL; // 변수 초기화
	for (int i = 0; i < n; i++) {
		// 모든 정점을 free한다.
		p = graph[i].adjacent;
		while (p != NULL) {
			// 모두 free
			q = p;
			p = p->next; // 진행
			free(q); // free 한다.
		}
	}
}

void dfs(Graph* graph, int n, int a, int* visited, int prev, int* isCycle) {
	visited[a - 1] = 1; // 방문
	edge* p = graph[a - 1].adjacent->next;
	while (p != NULL) {
		// 순서대로 방문
		if (visited[p->adVt - 1] == 1) {
			if (p->adVt != prev) // 바로 전에 방문했던 노드는 사이클이 아니다.
				(*isCycle)++; // 이미 방문한 적 있는 곳 다시 방문, 즉 사이클이 있다.
		}
		else
			dfs(graph, n, p->adVt, visited, a, isCycle); // 반복
		p = p->next; // 다음 정점
	}
}

int isTree(Graph* graph, int n) {
	// DFS를 사용해 트리인지 판별한다.
	int* visited = (int*)malloc(sizeof(int) * n); // 방문기록
	for (int i = 0; i < n; i++)
		visited[i] = 0; // 초기화
	int isCycle = 0; // 사이클이 있으면 0이 아님
	dfs(graph, n, 1, visited, 1, &isCycle); // 1 정점을 시작으로 탐색.
	if (isCycle > 0) {
		free(visited);
		return 0; // 사이클 존재, 트리 아님
	}
	else {
		for (int i = 0; i < n; i++)
			// 방문하지 않은 정점이 있다.
			if (visited[i] == 0) {
				free(visited);
				return 0;
			}
	}
	free(visited);
	return 1; // 트리이다.
}

int numberOfActive(int* inActice, int n) {
	// 활성화 되어있는 정점의 수
	int count = 0;
	for (int i = 0; i < n; i++)
		if (inActice[i] == 0) // 활성화 된 정점의 갯수를 센다.
			count++;
	return count;
}

void findCenter(Graph* graph, int n) {
	// 중심을 구한다.
	// 간선이 하나면 잎이다.
	int* inActice = (int*)malloc(sizeof(int) * n); // 삭제하지 않고 비활성화
	for (int i = 0; i < n; i++)
		inActice[i] = 0; // 모두 활성화
	int eccentricity = 0; // 이심률은 바깥의 잎, 정점을 삭제하는 횟수이다. (이동 간선의 개수)
	while (numberOfActive(inActice, n) > 2) {
		// 두개 이하로 정점이 남을 때 까지 반복
		eccentricity++; // 이심률 증가
		for (int i = 0; i < n; i++) {
			if (inActice[i] == 1) // 이미 비활성화 되어있으면 넘긴다.
				continue;
			// 모든 정점에 대해서 간선이 하나면 비활성화한다.
			int count = 0;
			edge* p = graph[i].adjacent->next; // 체크
			while (p != NULL) {
				// 아직 임시 비활성화된 2도 센다. 일괄로 처리해야 하기 때문에
				if (inActice[p->adVt - 1] == 0 || inActice[p->adVt - 1] == 2)  // 활성화 되어있을 때 
					count++; // 센다.
				p = p->next; // 다음으로
			}
			if (count == 1) // 비활성화 한다.
				inActice[i] = 2; // 하지만, 모든 정점 검사에서 이번 비활성화로 인해서 
				// 뒤에 정점 검사에 오류가 생기면 안되므로, 잠시 임시적으로 2로 표기한다.
		}
		// 모든 정점 검사가 끝나고, 일괄적으로 2로 임시 비활성화된 정점을 
		// 제대로 1로 비활성화 한다.
		for (int i = 0; i < n; i++)
			if (inActice[i] == 2)
				inActice[i] = 1; // 비활성화
	}
	int count = 0; // 중심의 개수 계산
	for (int i = 0; i < n; i++) { // 작은 순서대로
		if (inActice[i] == 0) {  // 마지막까지 활성화 되어 남음
			printf("%d ", i + 1); // 중심 출력
			count++; // 중심이다.
		}
	}
	if (count != 1) // 중심이 두 개라면, 이심률은 하나 더 멀어진다.
		eccentricity++;
	printf("\n%d", eccentricity); // 이심률 출력
	free(inActice); // free
}

void dfsOnlyChck(Graph* graph, int n, int a, int* visited) {
	visited[a - 1] = 1; // 방문
	edge* p = graph[a - 1].adjacent->next;
	while (p != NULL) {
		// 순서대로 방문
		if (visited[p->adVt - 1] == 0)  // 반복한 적이 없는 정점이라면
			dfsOnlyChck(graph, n, p->adVt, visited); // 방문
		p = p->next; // 다음 정점
	}
}

int isAllVisited(int* visited, int n) {
	// 모든 정점을 방문했는지 확인
	for (int i = 0; i < n; i++)
		if (visited[i] == 0) // 방문 안한 정점 있으니 더 반복해야 한다.
			return 1;
	return 0; // 모두 방문
}

int findConnectionElement(Graph* graph, int n) {
	// 연결요소 개수를 찾는다.
	int* visited = (int*)malloc(sizeof(int) * n); // 방문 기록
	int numberOfConnection = 0; // 연결요소 개수
	for (int i = 0; i < n; i++)
		visited[i] = 0; // 초기화
	int idx = 0; // 방문할 정점 인덱스
	while(isAllVisited(visited, n)) {
		// 모든 정점을 방문할 때 까지 반복, 한번 dfs를 시작할 때마다 연결요소가 하나씩 증가
		numberOfConnection++; // 연결요소 증가.
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) { // 아직 방문 안한 정점 있으면 멈춘다.
				idx = i; // 방문 안한 정점을 방문
				break;
			}
		}
		dfsOnlyChck(graph, n, idx + 1, visited); // 방문한다.
	}
	free(visited); // free
	return numberOfConnection; // 계산한 연결요소 개수를 반환한다.
}