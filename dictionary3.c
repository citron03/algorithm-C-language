#include <stdio.h>

void findding(int* a, int* b, char c, int* k);

int main() {

	int a, b, numYN, k;
	char c;
	scanf("%d %d %d", &a, &b, &numYN);
	getchar(); // 비우기
	for (int i = 0; i < numYN; i++) {
		scanf("%c", &c);
		findding(&a, &b, c, &k);
	}
	printf(" %d", k);
	return 0;
}


void findding(int* a, int* b, char c, int* k) {
	int m = (*a + *b) / 2;
	if (c == 'Y') // *k > m 이 맞다.
		*a = m + 1;
	else 
		// *k < m 이다.
		*b = m ;
	if (*a == *b)
		*k = *a;
	//printf("%d %d\n", *a, *b);
}

