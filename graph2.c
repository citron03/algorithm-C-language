#include <stdio.h>
#include <stdlib.h>

typedef struct edges {
	int V1, V2, E;
}edges;

void makeEdges(edges EG[]);
void makeAM(int AM[6][6]);
void printGraph(int a, int adjacencyMatrix[6][6], edges EG[21]);
void changeVertex(int a, int b, int w, int adjacencyMatrix[6][6], edges EG[21], int* idxEG);

int main() {
	// 인접행렬 구현
	int adjacencyMatrix[6][6], vertices[6];
	//int idxEG = 8;
	int idxEG = 0;
	edges EG[21];
	// 초기화
	for (int i = 0; i < 6; i++) {
		vertices[i] = i + 1;
		for (int j = 0; j < 6; j++)
			adjacencyMatrix[i][j] = -1;
	}
	//makeAM(adjacencyMatrix);
	//makeEdges(EG);
	// 입력
	changeVertex(1, 2, 1, adjacencyMatrix, EG, &idxEG);
	changeVertex(1, 3, 1, adjacencyMatrix, EG, &idxEG);
	changeVertex(1, 4, 1, adjacencyMatrix, EG, &idxEG);
	changeVertex(1, 6, 2, adjacencyMatrix, EG, &idxEG);
	changeVertex(2, 3, 1, adjacencyMatrix, EG, &idxEG);
	changeVertex(3, 5, 4, adjacencyMatrix, EG, &idxEG);
	changeVertex(5, 5, 4, adjacencyMatrix, EG, &idxEG);
	changeVertex(6, 5, 3, adjacencyMatrix, EG, &idxEG);
	char c;
	int a, b, w;
	while (1) {
		scanf("%c", &c);
		switch (c)
		{
		case 'a':
			scanf("%d", &a);
			printGraph(a, adjacencyMatrix, EG);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			changeVertex(a, b, w, adjacencyMatrix, EG, &idxEG);
			break;
		case 'q':
			return 0;
		}
	}

	return 0;
}


void makeEdges(edges EG[]) {
	// V1과 V2가 이어져 있으며, 가중치는 E
	// V1 > V2 항상
	EG[0].E = 1;
	EG[0].V1 = 1;
	EG[0].V2 = 2;

	EG[1].E = 1;
	EG[1].V1 = 1;
	EG[1].V2 = 3;

	EG[2].E = 1;
	EG[2].V1 = 1;
	EG[2].V2 = 4;

	EG[3].E = 2;
	EG[3].V1 = 1;
	EG[3].V2 = 6;

	EG[4].E = 1;
	EG[4].V1 = 2;
	EG[4].V2 = 3;

	EG[5].E = 4;
	EG[5].V1 = 3;
	EG[5].V2 = 5;

	EG[6].E = 4;
	EG[6].V1 = 5;
	EG[6].V2 = 5;

	EG[7].E = 3;
	EG[7].V1 = 5;
	EG[7].V2 = 6;
}

void makeAM(int AM[6][6]) {
	AM[0][1] = 0;
	AM[0][2] = 1;
	AM[0][3] = 2;
	AM[0][5] = 3;

	AM[1][0] = 0;
	AM[1][2] = 4;

	AM[2][0] = 1;
	AM[2][1] = 4;
	AM[2][4] = 5;

	AM[3][0] = 2;

	AM[4][2] = 5;
	AM[4][4] = 6;
	AM[4][5] = 7;

	AM[5][0] = 3;
	AM[5][4] = 7;
}

void printGraph(int a, int adjacencyMatrix[6][6], edges EG[21]) {
	if (a > 6 || a < 1) {
		printf("-1\n");
		return;
	}
	for (int i = 0; i < 6; i++) {
		if (adjacencyMatrix[a - 1][i] != -1) {
			if (EG[adjacencyMatrix[a - 1][i]].V1 == a && EG[adjacencyMatrix[a - 1][i]].E != 0)
				printf(" %d %d", EG[adjacencyMatrix[a - 1][i]].V2, EG[adjacencyMatrix[a - 1][i]].E);
			else if (EG[adjacencyMatrix[a - 1][i]].V2 == a && EG[adjacencyMatrix[a - 1][i]].E != 0)
				printf(" %d %d", EG[adjacencyMatrix[a - 1][i]].V1, EG[adjacencyMatrix[a - 1][i]].E);
		}
	}
	printf("\n");
}

void changeVertex(int a, int b, int w, int AM[6][6], edges EG[21], int* idxEG) {
	if (a > 6 || a < 1 || b > 6 || b < 1) {
		printf("-1\n");
		return;
	}

	if (AM[a - 1][b - 1] == -1) {
		AM[a - 1][b - 1] = *idxEG;
		AM[b - 1][a - 1] = *idxEG;
		EG[*idxEG].E = w;
		EG[*idxEG].V1 = a;
		EG[*idxEG].V2 = b;
		(*idxEG)++; // 다음 인덱스로
	}
	else {
		EG[AM[a - 1][b - 1]].E = w; // 갱신
	}
}