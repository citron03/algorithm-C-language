#include <stdio.h>

void insertItem(int key, int i);
void printArray();
void upHeap(int i);
void downHeap(int i, int last);
void inPlaceHeapSort();
void buildHeap();

int n, H[100];

int main() {

	// phase 1 : 최대힙을 만든다.
	buildHeap();
	// phase 2 : 만든 최대힙을 역으로 쌓아가며 배열을 작은 순서대로 정렬한다.
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
	// 0 위치를 사용하지 않고 1부터 시작하기 때문에
	// 2로 나눈 몫이 부모노드의 위치가 된다.
	if (H[i] > H[i / 2]) {
		// 부모 노드가 더 작으면 바꾼다.
		int tmp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = tmp;
	}
	upHeap(i / 2);
}
void  downHeap(int i, int last) {

	int left = i * 2, right = i * 2 + 1, biggest;

	// 외부 노드 도달
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