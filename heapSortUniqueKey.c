#include <stdio.h>

void insertItem(int key, int i);
void printArray();
void upHeap(int i);
void downHeap(int i, int last);
void inPlaceHeapSort();
void buildHeap();

int n, H[100];

int main() {

	// phase 1 : �ִ����� �����.
	buildHeap();
	// phase 2 : ���� �ִ����� ������ �׾ư��� �迭�� ���� ������� �����Ѵ�.
	inPlaceHeapSort();
	printArray();
	return 0;
}

void buildHeap() {
	scanf("%d", &n);
	int key;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &key);
		insertItem(key, i);
	}
}

void insertItem(int key, int i) {
	H[i] = key;
	upHeap(i);
}

void printArray() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}
void upHeap(int i) {

	// base case
	if (i == 1)
		return;
	// 0 ��ġ�� ������� �ʰ� 1���� �����ϱ� ������
	// 2�� ���� ���� �θ����� ��ġ�� �ȴ�.
	if (H[i] > H[i / 2]) {
		// �θ� ��尡 �� ������ �ٲ۴�.
		int tmp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = tmp;
	}
	upHeap(i / 2);
}
void  downHeap(int i, int last) {

	int left = i * 2, right = i * 2 + 1, biggest;

	// �ܺ� ��� ����
	if (left > last)
		return;

	biggest = left;

	if (right <= last)
		if (H[right] > H[biggest])
			biggest = right;
	if (H[i] >= H[biggest])
		return;

	int tmp = H[biggest];
	H[biggest] = H[i];
	H[i] = tmp;

	downHeap(biggest, last);
}

void inPlaceHeapSort() {
	int tmp;
	for (int i = n; i >= 2; i--) {
		tmp = H[1];
		H[1] = H[i];
		H[i] = tmp;
		downHeap(1, i - 1);
	}
}