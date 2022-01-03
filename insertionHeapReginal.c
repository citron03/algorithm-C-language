#include <stdio.h>
#include <stdlib.h>


void insertItem(int H[], int* idx, int num);
int removeMax(int H[], int* idx);
void upHeap(int H[], int idx);
void downHeap(int H[], int idx, int start);
void printHeap(int H[], int idx);
void swap(int H[], int i, int j);

int main() {

	int H[101], idx = 0, num;
	char act;

	while (1) {
		scanf("%c", &act);
		if (act == 'q')
			break;
		switch (act)
		{
		case 'i':
			scanf("%d", &num);
			insertItem(H, &idx, num);
			break;
		case 'd':
			printf("%d\n", removeMax(H, &idx));
			break;
		case 'p':
			printHeap(H, idx);
			break;
		}
	}

	return 0;
}


void insertItem(int H[], int* idx, int num) {
	*idx += 1;
	H[*idx] = num;
	upHeap(H, *idx);
	printf("0\n");
}
int removeMax(int H[], int* idx) {
	int R = H[1];
	H[1] = H[*idx];
	*idx -= 1;
	downHeap(H, *idx, 1);
	return R;
}
void upHeap(int H[], int idx) {
	if (idx / 2 < 1)
		return;
	if (H[idx] <= H[idx / 2])
		return;
	swap(H, idx, idx / 2);
	upHeap(H, idx / 2);
}
void downHeap(int H[], int idx, int start) {

	int next;
	if (start * 2 == idx)
		next = start * 2;
	else if (H[start * 2] > H[start * 2 + 1])
		next = start * 2;
	else
		next = start * 2 + 1;

	if (H[next] < H[start])
		return;
	swap(H, start, next);
	downHeap(H, idx, next);
}
void printHeap(int H[], int idx) {
	for (int i = 1; i <= idx; i++)
		printf(" %d", H[i]);
	printf("\n");
}
void swap(int H[], int i, int j) {
	int tmp = H[i];
	H[i] = H[j];
	H[j] = tmp;
}