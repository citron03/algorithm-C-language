#include <stdio.h>
#include <stdlib.h>

typedef struct Edges {
	struct Edges* next; // ����� �ٸ� ����, ������ NULL
	int adVt; // adjacent vertices, ����� ����
}edge;

typedef struct Graph {
	// �׷���, ���ܹ���. ��������Ʈ
	int verticesNum; // ���� ��ȣ
	edge* adjacent; // ������ ����� �ٸ� �������� ����Ʈ
}Graph;

void makeVertices(Graph* graph, int n); // �⺻����, �ʱ�ȭ
void initGraph(Graph* graph, int m); // ������ �Է¹޾� �ִ´�.
void freeEdges(Graph* graph, int n); // ���� ������ free
void insertEdge(Graph* graph, int a); // ���� ���� ����
int isTree(Graph* graph, int n); // Ʈ������ �˻�
void dfs(Graph* graph, int n, int a, int* visited, int prev, int* isCycle); // dfs�� Ʈ������ �˻��Ѵ�.
void findCenter(Graph* graph, int n); // �߽��� ���Ѵ�.
int numberOfActive(int* inActice, int n); // �߽��� ���ϴµ� ���� ������ ������
int findConnectionElement(Graph* graph, int n); // �׷����� ������ ������ ��ȯ�Ѵ�.
void dfsOnlyChck(Graph* graph, int n, int a, int* visited); // ������ ã�� ���� dfs
int isAllVisited(int* visited, int n);

int main() {
	int n, m;
	Graph* graph = NULL;
	scanf("%d %d", &n, &m); // ���� ������ ���� ������ �Է¹޴´�.
	graph = (Graph*)malloc(sizeof(Graph) * n);
	makeVertices(graph, n); // �׷��� �ʱ�ȭ
	initGraph(graph, m); // ���� ����
	//  G�� Ʈ������ �ƴ��� �˻�
	if (isTree(graph, n)) // Ʈ�����, �߽� ���. �� ���� ���� ���� ����.
		findCenter(graph, n);
	else // Ʈ���� �ƴϸ�, �׷����� �����ϴ� �������� ������ ����Ѵ�.
		printf("%d", findConnectionElement(graph, n));
	// free
	freeEdges(graph, n);
	free(graph);
	return 0;
}

void makeVertices(Graph* graph, int n) {
	for (int i = 1; i <= n; i++) {
		graph[i - 1].verticesNum = i; // ���� ��ȣ
		graph[i - 1].adjacent = (edge*)malloc(sizeof(edge)); // ��� ���
		graph[i - 1].adjacent->next = NULL;
	}
}

void insertEdge(Graph* graph, int a) {
	// ������ ���� ����Ʈ �����
	edge* p = (edge*)malloc(sizeof(edge));
	p->adVt = a;
	// �� �տ� �����Ѵ�.
	p->next = graph->adjacent->next;
	graph->adjacent->next = p;
}

void initGraph(Graph* graph, int m) {
	int a, b;
	for (int i = 0; i < m; i++) { // m���� ���� �߰�
		scanf("%d %d", &a, &b);
		// �� ������ ����� ���� ������ �����Ѵ�.
		insertEdge(&graph[a - 1], b);
		insertEdge(&graph[b - 1], a);
	}
}

void freeEdges(Graph* graph, int n) {
	edge* q = NULL, * p = NULL; // ���� �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		// ��� ������ free�Ѵ�.
		p = graph[i].adjacent;
		while (p != NULL) {
			// ��� free
			q = p;
			p = p->next; // ����
			free(q); // free �Ѵ�.
		}
	}
}

void dfs(Graph* graph, int n, int a, int* visited, int prev, int* isCycle) {
	visited[a - 1] = 1; // �湮
	edge* p = graph[a - 1].adjacent->next;
	while (p != NULL) {
		// ������� �湮
		if (visited[p->adVt - 1] == 1) {
			if (p->adVt != prev) // �ٷ� ���� �湮�ߴ� ���� ����Ŭ�� �ƴϴ�.
				(*isCycle)++; // �̹� �湮�� �� �ִ� �� �ٽ� �湮, �� ����Ŭ�� �ִ�.
		}
		else
			dfs(graph, n, p->adVt, visited, a, isCycle); // �ݺ�
		p = p->next; // ���� ����
	}
}

int isTree(Graph* graph, int n) {
	// DFS�� ����� Ʈ������ �Ǻ��Ѵ�.
	int* visited = (int*)malloc(sizeof(int) * n); // �湮���
	for (int i = 0; i < n; i++)
		visited[i] = 0; // �ʱ�ȭ
	int isCycle = 0; // ����Ŭ�� ������ 0�� �ƴ�
	dfs(graph, n, 1, visited, 1, &isCycle); // 1 ������ �������� Ž��.
	if (isCycle > 0) {
		free(visited);
		return 0; // ����Ŭ ����, Ʈ�� �ƴ�
	}
	else {
		for (int i = 0; i < n; i++)
			// �湮���� ���� ������ �ִ�.
			if (visited[i] == 0) {
				free(visited);
				return 0;
			}
	}
	free(visited);
	return 1; // Ʈ���̴�.
}

int numberOfActive(int* inActice, int n) {
	// Ȱ��ȭ �Ǿ��ִ� ������ ��
	int count = 0;
	for (int i = 0; i < n; i++)
		if (inActice[i] == 0) // Ȱ��ȭ �� ������ ������ ����.
			count++;
	return count;
}

void findCenter(Graph* graph, int n) {
	// �߽��� ���Ѵ�.
	// ������ �ϳ��� ���̴�.
	int* inActice = (int*)malloc(sizeof(int) * n); // �������� �ʰ� ��Ȱ��ȭ
	for (int i = 0; i < n; i++)
		inActice[i] = 0; // ��� Ȱ��ȭ
	int eccentricity = 0; // �̽ɷ��� �ٱ��� ��, ������ �����ϴ� Ƚ���̴�. (�̵� ������ ����)
	while (numberOfActive(inActice, n) > 2) {
		// �ΰ� ���Ϸ� ������ ���� �� ���� �ݺ�
		eccentricity++; // �̽ɷ� ����
		for (int i = 0; i < n; i++) {
			if (inActice[i] == 1) // �̹� ��Ȱ��ȭ �Ǿ������� �ѱ��.
				continue;
			// ��� ������ ���ؼ� ������ �ϳ��� ��Ȱ��ȭ�Ѵ�.
			int count = 0;
			edge* p = graph[i].adjacent->next; // üũ
			while (p != NULL) {
				// ���� �ӽ� ��Ȱ��ȭ�� 2�� ����. �ϰ��� ó���ؾ� �ϱ� ������
				if (inActice[p->adVt - 1] == 0 || inActice[p->adVt - 1] == 2)  // Ȱ��ȭ �Ǿ����� �� 
					count++; // ����.
				p = p->next; // ��������
			}
			if (count == 1) // ��Ȱ��ȭ �Ѵ�.
				inActice[i] = 2; // ������, ��� ���� �˻翡�� �̹� ��Ȱ��ȭ�� ���ؼ� 
				// �ڿ� ���� �˻翡 ������ ����� �ȵǹǷ�, ��� �ӽ������� 2�� ǥ���Ѵ�.
		}
		// ��� ���� �˻簡 ������, �ϰ������� 2�� �ӽ� ��Ȱ��ȭ�� ������ 
		// ����� 1�� ��Ȱ��ȭ �Ѵ�.
		for (int i = 0; i < n; i++)
			if (inActice[i] == 2)
				inActice[i] = 1; // ��Ȱ��ȭ
	}
	int count = 0; // �߽��� ���� ���
	for (int i = 0; i < n; i++) { // ���� �������
		if (inActice[i] == 0) {  // ���������� Ȱ��ȭ �Ǿ� ����
			printf("%d ", i + 1); // �߽� ���
			count++; // �߽��̴�.
		}
	}
	if (count != 1) // �߽��� �� �����, �̽ɷ��� �ϳ� �� �־�����.
		eccentricity++;
	printf("\n%d", eccentricity); // �̽ɷ� ���
	free(inActice); // free
}

void dfsOnlyChck(Graph* graph, int n, int a, int* visited) {
	visited[a - 1] = 1; // �湮
	edge* p = graph[a - 1].adjacent->next;
	while (p != NULL) {
		// ������� �湮
		if (visited[p->adVt - 1] == 0)  // �ݺ��� ���� ���� �����̶��
			dfsOnlyChck(graph, n, p->adVt, visited); // �湮
		p = p->next; // ���� ����
	}
}

int isAllVisited(int* visited, int n) {
	// ��� ������ �湮�ߴ��� Ȯ��
	for (int i = 0; i < n; i++)
		if (visited[i] == 0) // �湮 ���� ���� ������ �� �ݺ��ؾ� �Ѵ�.
			return 1;
	return 0; // ��� �湮
}

int findConnectionElement(Graph* graph, int n) {
	// ������ ������ ã�´�.
	int* visited = (int*)malloc(sizeof(int) * n); // �湮 ���
	int numberOfConnection = 0; // ������ ����
	for (int i = 0; i < n; i++)
		visited[i] = 0; // �ʱ�ȭ
	int idx = 0; // �湮�� ���� �ε���
	while(isAllVisited(visited, n)) {
		// ��� ������ �湮�� �� ���� �ݺ�, �ѹ� dfs�� ������ ������ �����Ұ� �ϳ��� ����
		numberOfConnection++; // ������ ����.
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) { // ���� �湮 ���� ���� ������ �����.
				idx = i; // �湮 ���� ������ �湮
				break;
			}
		}
		dfsOnlyChck(graph, n, idx + 1, visited); // �湮�Ѵ�.
	}
	free(visited); // free
	return numberOfConnection; // ����� ������ ������ ��ȯ�Ѵ�.
}