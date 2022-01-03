#include <stdio.h>
#include <stdlib.h>

void findIndex(int* p, int k, int* idx, int n);

int main() {

	int n, * p = NULL, k, idx;
	scanf("%d %d", &n, &k); // k�� ��ġ�� ã�´�.
	p = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);
	idx = n; // �ʱⰪ�� ������ �д�.
	findIndex(p, k, &idx, n);
	printf(" %d", idx);
	free(p); // �Ҵ�����
	return 0;
}


void findIndex(int* p, int k, int* idx, int n) {

	int left = 0, right = n - 1;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (p[mid] == k) { // ��ġ
			*idx = mid;
			return;
		}
		// ���� K���� ū �� �߿��� ���� ���� ��ġ ����
		if (p[mid] > k && *idx == n)
			*idx = mid; 
		else if (p[mid] > k && p[mid] < p[*idx])
			*idx = mid;
		// ���� �ݺ����� ����
		if (p[mid] < k)
			left = mid + 1;
		else
			right = mid - 1;
	}
}