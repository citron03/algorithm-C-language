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
	inPlaceQuickSort(p, 0, n - 1); // �����Ѵ�.
	for (int i = 0; i < n; i++)
		printf(" %d", p[i]);
	free(p); // �Ҵ� ����
	return 0;
}

int findPivot(int* p, int l, int r) {
	srand(time(NULL)); // �Ź� ���ο� ���� ����
	int pivot = rand() % (r + 1 - l) + l; // l <= pivot <= r
	return pivot;
}

void inPlacePartition(int* p, int l, int r, int k, int* a, int* b) {
	int pivot = p[k];
	swap(p, k, r); // pivot hide
	*a = l;
	*b = r - 1; // r�� pivot
	while (*a <= *b) {
		while (*a <= *b && p[*a] <= pivot) // �Ǻ����� ���� ���ȿ��� ��� ����
			(*a)++;
		while (*a <= *b && p[*b] >= pivot) // �Ǻ����� ū ���ȿ��� ����
			(*b)--;
		if (*a < *b) // ������ ������, �� �߰��� ��ġ�� ���� �ʴ� ���� ������ �ٲ�
			swap(p, *a, *b);
	}
	swap(p, *a, r); // �Ǻ��� ���� ��ġ�� �������´�
}

void inPlaceQuickSort(int* p, int l, int r) {
	if (l >= r)
		return;
	int k = findPivot(p, l, r); // �Ǻ�ã��
	int a, b;
	inPlacePartition(p, l, r, k, &a, &b); // �� ���� ����
	// a�� �������� ���� ������ �� �Ǻ����� ���� ��
	// b�� ���������� ���� ������ �� �Ǻ����� ū��
	inPlaceQuickSort(p, l, a - 1);
	inPlaceQuickSort(p, b + 1, r);
}

void swap(int* p, int l, int r) {
	// �� ������ ��ġ�� �ٲ�
	int tmp = p[l];
	p[l] = p[r];
	p[r] = tmp;
}