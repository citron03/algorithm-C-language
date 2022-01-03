#include <stdio.h>
#include <stdlib.h>

void findIndex(int left, int right, int* p, int k, int* idx);

int main() {

	int n, * p = NULL, k, idx;
	scanf("%d %d", &n, &k); // k의 위치를 찾는다.
	p = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) 
		scanf("%d", &p[i]);
	idx = -1; // 초기값을 설정해 둔다.
	findIndex(0, n - 1, p, k, &idx);
	printf(" %d", idx);
	free(p); // 할당해제
	return 0;
}


void findIndex(int left, int right, int* p, int k, int* idx) {

	if (left > right)
		return;
	int mid = (left + right) / 2;
	if (*idx == -1 && p[mid] < k) // 처음 값 저장.
		*idx = mid;
	else if (p[mid] < k && p[mid] > p[*idx]) // 지금 중앙값이 찾고자 하는 값보다는 작고, 지금까지 찾은 값보다는 클때 이를 저장
		*idx = mid;
	// k는 저장된 값, 인덱스가 아니다.
	if (p[mid] == k) {
		*idx = mid; // 일치하면 바로 그 값을 담고 멈춤.
		return;
	}
	else if (p[mid] > k)
		findIndex(left, mid - 1, p, k, idx);
	else
		findIndex(mid + 1, right, p, k, idx);
}