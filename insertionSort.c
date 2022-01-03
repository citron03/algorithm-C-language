#include <stdio.h>
#include <stdlib.h>

int findLocation(int *p, int n, int insert);
void makeWay(int* p, int n, int location);
void printAll(int* p, int n);
void insertion(int i, int* p, int insert);

int main() {

	int* p = NULL, n, i, tmp;
	scanf("%d", &n);
	p = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", &tmp);
		insertion(i, p, tmp);
	}
	printAll(p, n);
	free(p);
	return 0;
}

int findLocation(int* p, int n, int insert) {
	int i;
	for (i = 0; i < n; i++) 
		if (p[i] > insert)
			return i;
	return i - 1;
}


void makeWay(int* p, int n, int location) {
	for (int i = n + 1; i > location; i--) {
		p[i] = p[i - 1];
	}
}

void printAll(int* p, int n) {
	for (int i = 0; i < n; i++)
		printf(" %d", p[i]);
}

void insertion(int i, int* p, int insert) {

	int location;

	if (i == 0)
		p[0] = insert;
	else {
		// ÃÖ´ñ°ª Ã£±â
		location = findLocation(p, i + 1, insert);
		if (location == i)
			p[location] = insert;
		else {
			makeWay(p, i - 1, location);
			p[location] = insert;
		}
	}
}