#include <stdio.h>
#include <stdlib.h>


typedef struct Node {

	char elem;
	struct Node* next, * prev;

}Node;

// add(list, r, e) : list의 순위 r에 원소 e를 추가한다. 

void add(Node* list, int r, char e);
 
// delete(list, r) : list의 순위 r에 위치한 원소를 삭제한다. (주교재의 remove와 동일) 

void delete(Node* list, int r);

// get(list, r) : list의 순위 r에 위치한 원소를 반환한다. 

char get(Node* list, int r);

// print(list) : list의 모든 원소를 저장 순위대로 공백없이 출력한다.

void print(Node* list);

//※ 순위 정보가 유효하지 않으면 화면에 에러 메시지 "invalid position"을 출력하고, 해당연산을 무시한다.


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

	// 입력되는 위치는 1부터 시작한다.
	for (int i = 1; i < r; i++) {
		if (p->next == NULL || r < 1) {
			printf("invalid position\n");
			return;
		}
		p = p->next;
	}

	// 트레일러 노드 도달
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

		// 트레일러노드 도달
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