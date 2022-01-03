#include <stdio.h>
#include <stdlib.h>

void findIndex(int* p, int k, int* idx, int n);

int main() {

	int n, * p = NULL, k, idx;
	scanf("%d %d", &n, &k); // k의 위치를 찾는다.
	p = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);
	idx = n; // 초기값을 설정해 둔다.
	findIndex(p, k, &idx, n);
	printf(" %d", idx);
	free(p); // 할당해제
	return 0;
}


void findIndex(int* p, int k, int* idx, int n) {

	int left = 0, right = n - 1;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (p[mid] == k) { // 일치
			*idx = mid;
			return;
		}
		// 기준 K보다 큰 수 중에서 가장 작은 위치 저장
		if (p[mid] > k && *idx == n)
			*idx = mid; 
		else if (p[mid] > k && p[mid] < p[*idx])
			*idx = mid;
		// 다음 반복으로 진행
		if (p[mid] < k)
			left = mid + 1;
		else
			right = mid - 1;
	}
}