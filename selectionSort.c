#include <stdio.h>
#include <stdlib.h>

void sort(int* p, int n);
void printAll(int* p, int n);

int main() {

	int n, i, * p = NULL;
	scanf("%d", &n);
	p = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}
	sort(p, n);
	printAll(p, n);
	free(p);
	return 0;
}

void sort(int* p, int n) {

	int i, j, maxIndex, tmp;
	for(i = n - 1; i >= 0; i--) {
		// ���� ū ���� ã�Ƴ� ���� �ڷ� ������.
		maxIndex = 0;
		for (j = 1; j <= i; j++) {
			// ���� ū �� ã��
			if (p[maxIndex] < p[j])
				maxIndex = j;
		}
		// ��ü
		if (maxIndex != i) {
			tmp = p[i];
			p[i] = p[maxIndex];
			p[maxIndex] = tmp;
		}
	}

	/*
	int pass, j, minLoc, tmp;

	for (pass = 0; pass <= n - 2; pass++) {
		minLoc = pass;
		// ���ĵ��� ���� �ڸ����� ���� ���� ���� �ε����� ã�´�.
		for (j = pass + 1; j <= n - 1; j++)
			if (p[j] < p[minLoc])
				minLoc = j;
		// ��ü�Ͽ� ���� �ùٸ� ��ġ�� �����ش�.
		tmp = p[pass];
		p[pass] = p[minLoc];
		p[minLoc] = tmp;
	}
	*/
}


void printAll(int* p, int n) {
	for (int i = 0; i < n; i++)
		printf(" %d", p[i]);
}