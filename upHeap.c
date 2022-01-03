#include <stdio.h>
#include <stdlib.h>

void printHeap();
void downHeap(int i);
void rBuildHeap(int i);
void downHeapFor();

int H[101], n;

int main() {

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &H[i]);
	//rBuildHeap(1);
	downHeapFor();
	printHeap();
	return 0;
}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}

void  downHeap(int i) {
	// base case 
	if (i * 2 > n)
		return;
	int nextNode;
	if (i * 2 == n)
		nextNode = i * 2;
	else
		// 큰 값을 가진 자식 노드로 진행한다.
		nextNode = H[i * 2] > H[i * 2 + 1] ? i * 2 : i * 2 + 1;

	if (H[nextNode] < H[i])
		return;

	int tmp = H[nextNode];
	H[nextNode] = H[i];
	H[i] = tmp;
	downHeap(nextNode);
}


void rBuildHeap(int i) {
	if (i > n)
		return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
}

void downHeapFor() {
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
}