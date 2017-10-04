#include "library.h"

void addBook(LIST* bookList) {
	BOOK* newBook;
	NODE* bookNode;
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;

	newBook = (BOOK*)malloc(sizeof(BOOK));
	bookNode = (NODE*)malloc(sizeof(NODE));
	bookNode->data = newBook;

	if(HEAD == NULL) {
		bookList->head = bookNode;
		bookList->tail = bookNode;
	}
	else {
		TAIL->next = bookNode;
		bookNode->prev = TAIL;
		bookList->tail = bookNode;
	}

	inputBookInfo(newBook);
}

void inputBookInfo(BOOK* newBook) {
	printf("책 번호 입력: ");
	scanf("%d", &newBook->bookNumber);
	printf("책 이름 입력: ");
	fflush(stdin);
	gets(newBook->bookName);
	newBook->sign = 'O';
	newBook->userName = NULL;
}

///////////////////////////////////////////

void printBook(LIST* bookList) {
	NODE* bookNode;
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;

	if(HEAD == NULL) {
		printf("등록된 책이 없음.\n");
		return;
	}
	bookNode = HEAD;
	

	while(bookNode != TAIL) {
		printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
		printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
		printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
		printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
		bookNode = bookNode->next;
	}
	if(bookNode == TAIL) {
		printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
		printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
		printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
		printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
	}
	system("pause");
}

///////////////////////////////////////////

NODE* searchBook(LIST* bookList) {
	int num = 0;
	
	printf("[1] 책 번호 검색\n");
	printf("[2] 책 이름 검색\n");
	printf("번호 입력: ");
	scanf("%d", &num);
	
	if(num - 2) {
		return searchNumber(bookList);
	}
	else {
		return searchName(bookList);
	}
	return 0;
}

NODE* searchNumber(LIST* bookList) {
	NODE* bookNode;
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;
	
	int searchNumber = 0;

	printf("책 번호 입력: ");
	scanf("%d", &searchNumber);

	bookNode = HEAD;
	

	while(bookNode != TAIL) {
		if(searchNumber == ((BOOK*)bookNode->data)->bookNumber) {
			printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
			printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
			printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
			printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			system("pause");
			return bookNode;
		}
		bookNode = bookNode->next;
	}
	if(bookNode == TAIL) {
		if(searchNumber == ((BOOK*)bookNode->data)->bookNumber) {
			printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
			printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
			printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
			printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			system("pause");
			return bookNode;
		}
	}
	
	return 0;
}

NODE* searchName(LIST* bookList) {
	NODE* bookNode;
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;
	
	char searchName[BOOKLEN] = {NULL};
	
	printf("책 이름 입력: ");
	fflush(stdin);
	gets(searchName);

	bookNode = HEAD;
	

	while(bookNode != TAIL) {
		if(!strcmp(searchName, ((BOOK*)bookNode->data)->bookName)) {
			printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
			printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
			printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
			printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			system("pause");
			return bookNode;
		}
		bookNode = bookNode->next;
	}
	if(bookNode == TAIL) {
		if(!strcmp(searchName, ((BOOK*)bookNode->data)->bookName)) {
			printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
			printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
			printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
			printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			system("pause");
			return bookNode;
		}
	}
	return 0;
}

///////////////////////////////////////////

void modBook(LIST* bookList) {
	NODE* bookNode;
	int num = 0;

	printf("정보 수정할 책을 찾기 위한 검색 수행\n");
	bookNode = searchBook(bookList);

	printf("[1] 책 번호 수정\n");
	printf("[2] 책 제목 수정\n");

	printf("번호 입력: ");
	scanf("%d", &num);
	
	if(num - 2) {
		return modNumber(bookList, bookNode);
	}
	else {
		return modName(bookList, bookNode);
	}
}

void modNumber(LIST* bookList, NODE* bookNode) {
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;
	int num = 0;

	printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
	printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
	printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
	printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			
	printf("수정할 번호 입력: ");
	scanf("%d", &num);
	((BOOK*)bookNode->data)->bookNumber = num;

	printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
	printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
	printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
	printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
	printf("수정 완료\n");
	system("pause");
}

void modName(LIST* bookList, NODE* bookNode) {
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;
	
	char name[BOOKLEN];

	

	printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
	printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
	printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
	printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			
	printf("수정할 이름 입력: ");
	fflush(stdin);
	gets(name);
	strcpy(((BOOK*)bookNode->data)->bookName, name);

	printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
	printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
	printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
	printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
	printf("수정 완료\n");
}

///////////////////////////////////////////

void delBook(LIST* bookList) {
	NODE* bookNode;
	NODE* HEAD = bookList->head;
	NODE* TAIL = bookList->tail;

	printf("삭제할 책을 찾기 위한 검색 수행\n");
	bookNode = searchBook(bookList);

	if(HEAD == TAIL) {
	}
	else if(HEAD == bookNode) {
		bookList->head = bookNode->next;
		bookList->head->prev = NULL;
	}
	else if(TAIL == bookNode) {
		bookList->tail = bookNode->prev;
		bookList->tail->next = NULL;
	}
	else {
		bookNode->prev->next = bookNode->next;
		bookNode->next->prev = bookNode->prev;
	}
	free((BOOK*)bookNode->data);
	free(bookNode);
	printf("삭제 완료\n");
	system("pause");
}
