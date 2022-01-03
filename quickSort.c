#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int* p, int l, int r);
void inPlacePartition(int* p, int l, int r, int k, int* a, int* b);
void inPlaceQuickSort(int* p, int l, int r);
void swap(int* p, int l, int r);

int main() {

	int* p = NULL, n;
	scanf("%d", &n);
	p = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);
	inPlaceQuickSort(p, 0, n - 1); // 정렬한다.
	for (int i = 0; i < n; i++)
		printf(" %d", p[i]);
	free(p); // 할당 해제
	return 0;
}

int findPivot(int* p, int l, int r) {
	srand(time(NULL)); // 매번 새로운 난수 생성
	int pivot = rand() % (r + 1 - l) + l; // l <= pivot <= r
	return pivot;
}

void inPlacePartition(int* p, int l, int r, int k, int* a, int* b) {
	int pivot = p[k];
	swap(p, k, r); // pivot hide
	*a = l;
	*b = r - 1; // r은 pivot
	while (*a <= *b) {
		while (*a <= *b && p[*a] <= pivot) // 피봇보다 작은 동안에는 계속 전진
			(*a)++;
		while (*a <= *b && p[*b] >= pivot) // 피봇보다 큰 동안에는 후퇴
			(*b)--;
		if (*a < *b) // 끝까지 못오면, 즉 중간에 위치에 맞지 않는 숫자 있으면 바꿈
			swap(p, *a, *b);
	}
	swap(p, *a, r); // 피봇을 원래 위치로 돌려놓는다
}

void inPlaceQuickSort(int* p, int l, int r) {
	if (l >= r)
		return;
	int k = findPivot(p, l, r); // 피봇찾기
	int a, b;
	inPlacePartition(p, l, r, k, &a, &b); // 두 개로 분할
	// a는 왼쪽으로 부터 보았을 때 피봇보다 작은 것
	// b는 오른쪽으로 부터 보았을 때 피봇보다 큰것
	inPlaceQuickSort(p, l, a - 1);
	inPlaceQuickSort(p, b + 1, r);
}

void swap(int* p, int l, int r) {
	// 두 변수의 위치를 바꿈
	int tmp = p[l];
	p[l] = p[r];
	p[r] = tmp;
}