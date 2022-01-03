#include <stdio.h>
#include <stdlib.h>

void printAll(int* p, int n);
void insertionSort(int *p, int  n);

int main() {

	int* p = NULL, n, i;
	scanf("%d", &n);
	p = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}
	insertionSort(p, n);
	printAll(p, n);
	free(p);
	return 0;
}


void insertionSort(int* p, int  n) {

	for (int i = 1; i < n; i++) {
		// 두번째 요소부터 검증한다.
		int j = i - 1;
		int save = p[i];
		while (p[j] > save && j >= 0) {
			// 위치를 찾는다.
			p[j + 1] = p[j];
			j--;
		}
		p[j + 1] = save;
	}

}