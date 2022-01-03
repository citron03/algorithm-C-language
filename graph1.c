#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	struct list* next;
	int idx;
}list;

typedef struct edges {
	int V1, V2, E;
}edges;

typedef struct vertices {
	struct list* incidence;
	int ele;
}vertices;

void makeVertices(vertices VT[]);
void printNodeNum(vertices VT[], edges EG[], int a);
void changeEdge(vertices VT[], edges EG[], int a, int b, int w, int* EGidx);
void connectEdge(vertices VT[], edges EG[], int a, int b, int* EGidx);
void freeNode(vertices VT[]);

int main() {
	// ��������Ʈ ����
	vertices VT[6];
	edges EG[21];
	//int EGidx = 8;
	int EGidx = 0;
	// �׷��� �׸���
	makeVertices(VT);
	changeEdge(VT, EG, 1, 2, 1, &EGidx);
	changeEdge(VT, EG, 1, 3, 1, &EGidx);
	changeEdge(VT, EG, 1, 4, 1, &EGidx);
	changeEdge(VT, EG, 1, 6, 2, &EGidx);
	changeEdge(VT, EG, 2, 3, 1, &EGidx);
	changeEdge(VT, EG, 3, 5, 4, &EGidx);
	changeEdge(VT, EG, 5, 5, 4, &EGidx);
	changeEdge(VT, EG, 6, 5, 3, &EGidx);
	// �Է¹ޱ�
	char c;
	int a, b, w;
	while (1) {
		scanf("%c", &c);
		switch (c)
		{
		case 'a':
			scanf("%d", &a);
			printNodeNum(VT, EG, a);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			changeEdge(VT, EG, a, b, w, &EGidx);
			break;
		case 'q':
			return 0;
		}
	}
	freeNode(VT);
	return 0;
}

void makeVertices(vertices VT[]) {
	for (int i = 0; i < 6; i++) {
		VT[i].ele = i + 1;
		VT[i].incidence = (list*)malloc(sizeof(list));
		VT[i].incidence->next = NULL; // �ʱ�ȭ
	}
}


void printNodeNum(vertices VT[], edges EG[], int a) {
	if (a > 6 || a < 1) {
		printf("-1\n");
		return;
	}
	list* p = VT[a - 1].incidence->next;
	int e;
	while (p != NULL) {
		e = p->idx;
		// ��� ��ȣ�� ����ġ ���
		if (EG[e].V1 == a && EG[e].E != 0) {
			printf(" %d %d", EG[e].V2, EG[e].E);
			p = p->next;
		}
		else if (EG[e].V2 == a && EG[e].E != 0) {
			printf(" %d %d", EG[e].V1, EG[e].E);
			p = p->next;
		}
		else
			p = p->next;
	}
	printf("\n");
}

void changeEdge(vertices VT[], edges EG[], int a, int b, int w, int* EGidx) {
	if (a > 6 || a < 1) {
		printf("-1\n");
		return;
	}
	if (b > 6 || b < 1) {
		printf("-1\n");
		return;
	} // a�� b ������ �������� ������ ����
	list* p = VT[a - 1].incidence->next;
	int e;

	while (p != NULL) {
		e = p->idx;
		if ((EG[e].V1 == a && EG[e].V2 == b) ||
			(EG[e].V1 == b && EG[e].V2 == a)) {
			EG[e].E = w;
			return;
		}
		else {
			if (p == NULL)
				break;
			p = p->next;
		}
		// ���� w �� 0�̸� ����
	}
	if (p == NULL) {
		// ��ã��. ���� �߰��ؾ� �Ѵ�.
		EG[*EGidx].V1 = a;
		EG[*EGidx].V2 = b;
		EG[*EGidx].E = w;
		// �� ����Ʈ ���� edges����
		connectEdge(VT, EG, a, b, EGidx);
		if (a == b) { // �����϶�
			(*EGidx)++; // ���� �ε�����
			return;
		}
		// �ݴ�� ����
		connectEdge(VT, EG, b, a, EGidx);
		(*EGidx)++; // ���� �ε�����
	}
}

void freeNode(vertices VT[]) {
	list* p = NULL, * q = NULL;
	for (int i = 0; i < 6; i++) {
		p = VT[i].incidence;
		while (p != NULL) {
			q = p;
			p = p->next;
			free(q);
		}
	}
}

void connectEdge(vertices VT[], edges EG[], int a, int b, int* EGidx) {
	// �� ����Ʈ ���� edges����
	list* np1 = (list*)malloc(sizeof(list));
	np1->next = NULL;
	np1->idx = *EGidx;
	list* p = VT[a - 1].incidence; // a ��ġ ã��
	while (p != NULL) {
		// ������ ��ġ ����
		if (p->next == NULL) {
			// �������� ����
			p->next = np1;
			break;
		}
		// �������� ����� ���ؼ� ��ġ�� ã�ƾ� �Ѵ�.
		if (EG[p->next->idx].V1 == a) {
			// b�� V2�� ���� ������ ��ġ���� Ȯ���Ѵ�.
			if (EG[p->next->idx].V2 > b) {
				// ����
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		else if (EG[p->next->idx].V2 == a) {
			// b�� V1�� ���� ������ ��ġ���� Ȯ���Ѵ�.
			if (EG[p->next->idx].V1 > b) {
				// ����
				np1->next = p->next;
				p->next = np1;
				break;
			}
		}
		p = p->next; // ��ã������ ��������
	}
}