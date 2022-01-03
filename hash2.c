#include <stdio.h>
#include <stdlib.h>

void insertItem(int* hash, int e, int M);
int searching(int* hash, int e, int M);

int main() {
	// 개방주소법 해시테이블 - 선형조사법
	int M, n, * hash = NULL, ele;
	char c;
	scanf("%d %d", &M, &n);
	hash = (int*)malloc(sizeof(int) * M);
	for (int i = 0; i < M; i++)
		hash[i] = 0;

	while (1) {
		// 삽입
		scanf("%c", &c);
		switch (c)
		{
		case 'i':
			scanf("%d", &ele);
			insertItem(hash, ele, M);
			break;
		case 's':
			scanf("%d", &ele);
			int idx = searching(hash, ele, M);
			if (idx == -1)
				printf("-1\n");
			else
				printf("%d %d\n", idx, hash[idx]);
			break;
		case 'e':
			free(hash);
			return 0;
		}
	}
	free(hash);
	return 0;
}


void insertItem(int* hash, int e, int M) {
	int idx = e % M;
	while (1) {
		if (hash[idx] == 0) {
			hash[idx] = e;
			printf("%d\n", idx);
			return;
		}
		else {
			idx = (idx + 1) % M; // 1을 전진 시킨다. 그리고 원형으로
			printf("C"); // 충돌 출력
		}
	}
}

int searching(int* hash, int e, int M) {
	int idx = e % M;
	for (int i = 0; i < M; i++) {
		if (hash[idx] == e)
			return idx;
		else 
			idx = (idx + 1) % M; // 1을 전진 시킨다. 그리고 원형으로
	}
	return -1; // 못찾으면
}