#include <stdio.h>
#include <stdlib.h>

void findIndex(int left, int right, int* p, int k, int* idx);

int main() {

	int n, * p = NULL, k, idx;
	scanf("%d %d", &n, &k); // k�� ��ġ�� ã�´�.
	p = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) 
		scanf("%d", &p[i]);
	idx = -1; // �ʱⰪ�� ������ �д�.
	findIndex(0, n - 1, p, k, &idx);
	printf(" %d", idx);
	free(p); // �Ҵ�����
	return 0;
}


void findIndex(int left, int right, int* p, int k, int* idx) {

	if (left > right)
		return;
	int mid = (left + right) / 2;
	if (*idx == -1 && p[mid] < k) // ó�� �� ����.
		*idx = mid;
	else if (p[mid] < k && p[mid] > p[*idx]) // ���� �߾Ӱ��� ã���� �ϴ� �����ٴ� �۰�, ���ݱ��� ã�� �����ٴ� Ŭ�� �̸� ����
		*idx = mid;
	// k�� ����� ��, �ε����� �ƴϴ�.
	if (p[mid] == k) {
		*idx = mid; // ��ġ�ϸ� �ٷ� �� ���� ��� ����.
		return;
	}
	else if (p[mid] > k)
		findIndex(left, mid - 1, p, k, idx);
	else
		findIndex(mid + 1, right, p, k, idx);
}