#include <stdio.h>
#include <stdlib.h>


typedef struct Node {

	char elem;
	struct Node* next, * prev;

}Node;

// add(list, r, e) : list�� ���� r�� ���� e�� �߰��Ѵ�. 

void add(Node* list, int r, char e);
 
// delete(list, r) : list�� ���� r�� ��ġ�� ���Ҹ� �����Ѵ�. (�ֱ����� remove�� ����) 

void delete(Node* list, int r);

// get(list, r) : list�� ���� r�� ��ġ�� ���Ҹ� ��ȯ�Ѵ�. 

char get(Node* list, int r);

// print(list) : list�� ��� ���Ҹ� ���� ������� ������� ����Ѵ�.

void print(Node* list);

//�� ���� ������ ��ȿ���� ������ ȭ�鿡 ���� �޽��� "invalid position"�� ����ϰ�, �ش翬���� �����Ѵ�.


int main() {

	int n, place;
	char cal, elem;

	Node* Header = (Node*)malloc(sizeof(Node));
	Node* Trailer = (Node*)malloc(sizeof(Node));

	Header->next = Trailer;
	Header->prev = NULL;
	Trailer->prev = Header;
	Trailer->next = NULL;

	scanf("%d", &n);


	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &cal);

		switch (cal)
		{
		case 'A' :
			scanf("%d", &place); 
			getchar();
			scanf("%c", &elem);
			add(Header, place, elem);
			break;

		case 'D':
			scanf("%d", &place);
			delete(Header, place);
			break;

		case 'G':
			scanf("%d", &place);

			char getNow = get(Header, place);

			if (getNow == '0') {
				printf("invalid position\n");
				break;
			}
			else {
				printf("%c\n", getNow);
			}
			break;

		case 'P':
			print(Header);
			break;
		}

	}

	Node* p = Header;
	Node* q = NULL;

	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}

	return 0;
}

void add(Node* list, int r, char e) {

	Node* p = list;

	// �ԷµǴ� ��ġ�� 1���� �����Ѵ�.
	for (int i = 1; i < r; i++) {
		if (p->next == NULL || r < 1) {
			printf("invalid position\n");
			return;
		}
		p = p->next;
	}

	// Ʈ���Ϸ� ��� ����
	if (p->next == NULL) {
		printf("invalid position\n");
		return;
	}

	Node* insert = (Node*)malloc(sizeof(Node));

	insert->elem = e;

	insert->next = p->next;
	p->next->prev = insert;
	p->next = insert;
	insert->prev = p;

}


void delete(Node* list, int r) {


	Node* p = list;

	for (int i = 0; i < r; i++) {
		p = p->next;
		if (p->next == NULL || r < 1) {
			printf("invalid position\n");
			return;
		}
	}

	p->next->prev = p->prev;
	p->prev->next = p->next;

	free(p);

}

char get(Node* list, int r) {


	Node* p = list;

	for (int i = 0; i < r; i++) {

		p = p->next;

		// Ʈ���Ϸ���� ����
		if (p->next == NULL || r < 1) {
			return '0';
		}
	}

	return p->elem;

}

void print(Node* list) {

	Node* p = list->next;

	while (p->next != NULL) {
		printf("%c", p->elem);
		p = p->next;
	}
	printf("\n");
}