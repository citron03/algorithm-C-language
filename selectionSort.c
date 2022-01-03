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
		// 가장 큰 것을 찾아내 가장 뒤로 보낸다.
		maxIndex = 0;
		for (j = 1; j <= i; j++) {
			// 가장 큰 것 찾기
			if (p[maxIndex] < p[j])
				maxIndex = j;
		}
		// 교체
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
		// 정렬되지 않은 자리부터 가장 작은 값의 인덱스를 찾는다.
		for (j = pass + 1; j <= n - 1; j++)
			if (p[j] < p[minLoc])
				minLoc = j;
		// 교체하여 값의 올바른 위치를 정해준다.
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