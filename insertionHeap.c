#include <stdio.h>
#include <stdlib.h>

int H[101], n = 0;

void insertItem(int key);
int removeMax();
void printHeap();
void upHeap(int i);
void downHeap(int i);

int main() {

	char enter;
	int i;

	while (1) {
		scanf("%c", &enter);
		switch (enter)
		{
		case 'q':
			return 0;
			break;
		case 'i':
			scanf("%d", &i);
			insertItem(i);
			break;
		case 'd':
			printf("%d\n", removeMax());
			break;
		case 'p':
			printHeap();
			break;
		}

	}


	return 0;
}



void insertItem(int key) {
	n += 1;
	H[n] = key;
	upHeap(n);
	printf("0\n");
}
int removeMax() {
	int key = H[1];
	H[1] = H[n];
	n = n - 1;
	downHeap(1);
	return key;
}
void printHeap() {
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
void  downHeap(int i) {
	// base case 
	if (i * 2 > n)
		return;
	int nextNode;
	if (i * 2 == n)
		nextNode = i * 2;
	else 
		// ū ���� ���� �ڽ� ���� �����Ѵ�.
		nextNode = H[i * 2] > H[i * 2 + 1] ? i * 2 : i * 2 + 1;
	
	if (H[nextNode] < H[i])
		return;

	int tmp = H[nextNode];
	H[nextNode] = H[i];
	H[i] = tmp;
	downHeap(nextNode);
}