#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <Windows.h>

void sort(int* p, int n);
void insertionSort(int* p, int  n);

int main() {
	// �ʿ��� ������ ���������� ���� srand�� �����Ѵ�.
	int n, * A = NULL, * B = NULL, tmp;
	srand(time(NULL));

	// ���� �����͸� �̿��� �� ���Ǵ� �ڵ��
	//scanf("%d", &n);
	//A = (int*)malloc(sizeof(int) * n);
	//B = (int*)malloc(sizeof(int) * n);
	//  �迭 A�� ���ؼ��� ���� ������, �迭 B�� ���ؼ��� ���� ������ ����

	// 10000���� ���Ҹ� ���� �迭���� �����Ͽ� 100000���� ������ ������ �����ϸ� 10ȸ �ݺ�.
	for (n = 10000; n <= 100000; n += 10000) {
		printf("---- ���� %d ���� ���Ҹ� �׽�Ʈ ���Դϴ�. ----\n", n);
		A = (int*)malloc(sizeof(int) * n);
		B = (int*)malloc(sizeof(int) * n);
		
		/*
		// ���� ���� �ʱ�ȭ, A case
		for (int i = 0; i < n; i++) {
			tmp = rand() % 110000 + 1;
			A[i] = tmp;
			B[i] = tmp;
		}
		*/
		/*
		// ���ĵ� ������, B���̽�
		for (int i = 0; i < n; i++) {
			A[i] = i;
			B[i] = i;
		}
		*/
		
		// �������� ���ĵ� ������, C���̽�
		for (int i = n - 1; i >= 0; i--) {
			A[n - i - 1] = i;
			B[n - i - 1] = i;
		}
		

		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		sort(A, n); // ���� ����
		QueryPerformanceCounter(&end);
		// ���������κ��� ����ð� ���
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		insertionSort(B, n);	// ���� ����
		QueryPerformanceCounter(&end);
		// ���������κ��� ����ð� ���
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		// ����� ���� �迭�� free�Ѵ�.
		free(A);
		free(B);
	}

	return 0;
}
void sort(int* p, int n) {

	int pass, j, minLoc, tmp;

	for (pass = 0; pass <= n - 2; pass++) {
		minLoc = pass;
		// ���ĵ��� ���� �ڸ����� ���� ���� ���� �ε����� ã�´�.
		for (j = pass + 1; j <= n - 1; j++)
			if (p[j] < p[minLoc])
				minLoc = j;
		// ��ü�Ͽ� ���� �ùٸ� ��ġ�� �����ش�.
		tmp = p[pass];
		p[pass] = p[minLoc];
		p[minLoc] = tmp;
	}

}
void insertionSort(int* p, int  n) {

	for (int i = 1; i < n; i++) {
		// �ι�° ��Һ��� �����Ѵ�.
		int j = i - 1;
		int save = p[i];
		while (p[j] > save && j >= 0) {
			// ��ġ�� ã�´�.
			p[j + 1] = p[j];
			j--;
		}
		// ã�Ƴ� ��ġ�� �����͸� �����Ѵ�.
		p[j + 1] = save;
	}

}
