#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <Windows.h>

void sort(int* p, int n);
void insertionSort(int* p, int  n);

int main() {
	// 필요한 변수와 랜덤변수를 위한 srand를 설정한다.
	int n, * A = NULL, * B = NULL, tmp;
	srand(time(NULL));

	// 랜덤 데이터를 이용할 때 사용되는 코드들
	//scanf("%d", &n);
	//A = (int*)malloc(sizeof(int) * n);
	//B = (int*)malloc(sizeof(int) * n);
	//  배열 A에 대해서는 선택 정렬을, 배열 B에 대해서는 삽입 정렬을 수행

	// 10000개의 원소를 갖는 배열부터 시작하여 100000개씩 원소의 갯수가 증가하며 10회 반복.
	for (n = 10000; n <= 100000; n += 10000) {
		printf("---- 현재 %d 개의 원소를 테스트 중입니다. ----\n", n);
		A = (int*)malloc(sizeof(int) * n);
		B = (int*)malloc(sizeof(int) * n);
		
		/*
		// 랜덤 변수 초기화, A case
		for (int i = 0; i < n; i++) {
			tmp = rand() % 110000 + 1;
			A[i] = tmp;
			B[i] = tmp;
		}
		*/
		/*
		// 정렬된 데이터, B케이스
		for (int i = 0; i < n; i++) {
			A[i] = i;
			B[i] = i;
		}
		*/
		
		// 역순으로 정렬된 데이터, C케이스
		for (int i = n - 1; i >= 0; i--) {
			A[n - i - 1] = i;
			B[n - i - 1] = i;
		}
		

		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		sort(A, n); // 선택 정렬
		QueryPerformanceCounter(&end);
		// 측정값으로부터 실행시간 계산
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		insertionSort(B, n);	// 삽입 정렬
		QueryPerformanceCounter(&end);
		// 측정값으로부터 실행시간 계산
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		// 사용이 끝난 배열을 free한다.
		free(A);
		free(B);
	}

	return 0;
}
void sort(int* p, int n) {

	int pass, j, minLoc, tmp;

	for (pass = 0; pass <= n - 2; pass++) {
		minLoc = pass;
		// 정렬되지 않은 자리부터 가장 작은 값의 인덱스를 찾는다.
		for (j = pass + 1; j <= n - 1; j++)
			if (p[j] < p[minLoc])
				minLoc = j;
		// 교체하여 값의 올바른 위치를 정해준다.
		tmp = p[pass];
		p[pass] = p[minLoc];
		p[minLoc] = tmp;
	}

}
void insertionSort(int* p, int  n) {

	for (int i = 1; i < n; i++) {
		// 두번째 요소부터 검증한다.
		int j = i - 1;
		int save = p[i];
		while (p[j] > save && j >= 0) {
			// 위치를 찾는다.
			p[j + 1] = p[j];
			j--;
		}
		// 찾아낸 위치에 데이터를 저장한다.
		p[j + 1] = save;
	}

}
