#include <stdio.h>
#include <stdlib.h>

void insertItem(int* hash, int e, int M, int q);
int searching(int* hash, int e, int M, int q);
void printHash(int* hash, int M);

int main() {
	// �����ּҹ� �ؽ����̺� - ���������
	int M, n, q, * hash = NULL, ele;
	char c;
	scanf("%d %d %d", &M, &n, &q);
	hash = (int*)malloc(sizeof(int) * M);
	for (int i = 0; i < M; i++)
		hash[i] = 0;

	while (1) {
		// ����
		scanf("%c", &c);
		switch (c)
		{
		case 'i':
			scanf("%d", &ele);
			insertItem(hash, ele, M, q);
			break;
		case 's':
			scanf("%d", &ele);
			int idx = searching(hash, ele, M, q);
			if (idx == -1)
				printf("-1\n");
			else
				printf("%d %d\n", idx, hash[idx]);
			break;
		case 'p':
			printHash(hash, M);
			break;
		case 'e':
			printHash(hash, M);
			free(hash);
			return 0;
		}
	}
	free(hash);
	return 0;
}


void insertItem(int* hash, int e, int M, int q) {
	int idx = e % M;
	while (1) {
		if (hash[idx] == 0) {
			hash[idx] = e;
			printf("%d\n", idx);
			return;
		}
		else {
			idx = (idx + q - (e % q)) % M; // �ߺ��� �� ��° �ؽ� �Լ�
			printf("C"); // �浹 ���
		}
	}
}

int searching(int* hash, int e, int M, int q) {
	int idx = e % M;
	for (int i = 0; i < M; i++) {
		if (hash[idx] == e)
			return idx;
		else
			idx = (idx + q - (e % q)) % M; // �ߺ��� �� ��° �ؽ� �Լ�
	}
	return -1; // ��ã����
}

void printHash(int* hash, int M) {
	for (int i = 0; i < M; i++)
		printf(" %d", hash[i]);
	printf("\n");
}