#include "books.h"

/*
Add();
Print();
Search();
Modify();
Delete();
Exit();
*/

int bookCount = 1;
book* allBooks;

void Add(void) {
	int i = 0;
	book newBook;
	book* books = (book*)malloc(sizeof(book)*bookCount);
	srand(time(NULL));
	newBook.bookNumber = rand()+10000;
	printf("======================================\n");
	for(i = 0; i < bookCount - 1; i++) {
		while(newBook.bookNumber == allBooks[i].bookNumber) {
			srand(time(NULL));
			newBook.bookNumber = rand()+10000;
			i--;
		}
	}
	printf("책 제목: ");
	scanf("%s", newBook.title);
	printf("작가명: ");
	scanf("%s", newBook.writer);
	for(i = 0; i < bookCount - 1; i++) {
		books[i] = allBooks[i];
	}
	books[i] = newBook;
	bookCount++;

	allBooks = books;
	
	printf("======================================\n");
	printf("추가된 책의 정보는 다음과 같습니다.\n");
	printf("======================================\n");
	printf("책 번호: %d\n", books[i].bookNumber);
	printf("책 제목: %s\n", books[i].title);
	printf("작가명: %s\n", books[i].writer);
	printf("======================================\n");
//	printf("%d %s %s\n", allBooks[0].bookNumber, allBooks[0].title, allBooks[0].writer); // 출력 확인
	system("pause");
}

void Print(const book* books) {
	int i = 0;
	printf("======================================\n");
	for(i = 0; i < bookCount - 1; i++) {
		printf("책 번호: %d\n", books[i].bookNumber);
		printf("책 제목: %s\n", books[i].title);
		printf("작가명: %s\n", books[i].writer);
		printf("======================================\n");
	}
	printf("모두 출력하였습니다.\n");
	printf("======================================\n");
	system("pause");
}

void Search(const book* books) {
	int bookNumber;
	char title[30];
	char writer[30];
	int i = 0;
	int num = 0;
	int check = 0;

	printf("======================================\n");
	printf("[1] 책 번호로 찾기\n");
	printf("[2] 책 제목으로 찾기\n");
	printf("[3] 작가명으로 찾기\n");
	printf("======================================\n");
	printf("번호를 선택해주세요: ");
	scanf("%d", &num);
	if(0>=num || 3 < num) {
		printf("======================================\n");
		printf("잘못 입력하셨습니다.\n");
		printf("======================================\n");
		fflush(stdin);
		return;
	}
	printf("======================================\n");
	switch(num) {
	case 1:
		printf("책 번호 입력: ");
		scanf("%d", &bookNumber);
		fflush(stdin);
		for(i = 0; i < bookCount - 1; i++) {
			if(bookNumber == books[i].bookNumber) {
				printf("======================================\n");
				printf("책 번호: %d\n", books[i].bookNumber);
				printf("책 제목: %s\n", books[i].title);
				printf("작가명: %s\n", books[i].writer);
				printf("======================================\n");
				system("pause");
				return;
			}
		}
		break;
	case 2:
		printf("책 제목 입력: ");
		scanf("%s", title);
		fflush(stdin);
		for(i = 0; i < bookCount - 1; i++) {
			if(!strcmp(title, books[i].title)) {
				printf("======================================\n");
				printf("책 번호: %d\n", books[i].bookNumber);
				printf("책 제목: %s\n", books[i].title);
				printf("작가명: %s\n", books[i].writer);
				check++;
			}
		}
		break;
	case 3:
		printf("작가명 입력: ");
		scanf("%s", writer);
		fflush(stdin);
		for(i = 0; i < bookCount - 1; i++) {
			if(!strcmp(writer, books[i].writer)) {
				printf("======================================\n");
				printf("책 번호: %d\n", books[i].bookNumber);
				printf("책 제목: %s\n", books[i].title);
				printf("작가명: %s\n", books[i].writer);
				check++;
			}
		}
		break;
	}
	printf("======================================\n");
	printf("검색 완료\n");
	printf("======================================\n");
	if(check == 0) {
		printf("해당하는 책을 찾을 수 없습니다.\n");
		printf("======================================\n");
	}
	system("pause");
}

void Modify(book* books) {
	int bookNumber;
	char title[30];
	char writer[30];
	int num = 0;
	int i = 0;

	printf("======================================\n");
	printf("책 번호 입력: ");
	scanf("%d", &bookNumber);
	fflush(stdin);
	for(i = 0; i < bookCount - 1; i++) {
		if(bookNumber == books[i].bookNumber) {
			printf("======================================\n");
			printf("어떤 부분을 수정하시겠습니까?\n");
			printf("======================================\n");
			printf("[1] 책 번호: %d\n", books[i].bookNumber);
			printf("[2] 책 제목: %s\n", books[i].title);
			printf("[3] 작가명: %s\n", books[i].writer);
			printf("======================================\n");
			printf("번호를 입력해주세요: ");
			scanf("%d", &num);
			if(0 >= num || 3 < num) {
				printf("======================================\n");
				printf("잘못 입력하셨습니다.\n");
				printf("======================================\n");
				fflush(stdin);
				return;
			}
			printf("======================================\n");
			switch(num) {
			case 1:
				printf("어떤 번호로 수정하시겠습니까? ");
				scanf("%d", &bookNumber);
				fflush(stdin);
				books[i].bookNumber = bookNumber;
				break;
			case 2:
				printf("어떤 제목으로 수정하시겠습니까? ");
				scanf("%s", title);
				fflush(stdin);
				strcpy(books[i].title, title);
				break;
			case 3:
				printf("어떤 이름으로 수정하시겠습니까? ");
				scanf("%s", writer);
				fflush(stdin);
				strcpy(books[i].writer, writer);
				break;
			}
			printf("======================================\n");
			printf("다음과 같은 정보로 수정되었습니다.\n");
			printf("======================================\n");
			printf("책 번호: %d\n", books[i].bookNumber);
			printf("책 제목: %s\n", books[i].title);
			printf("작가명: %s\n", books[i].writer);
			printf("======================================\n");
			system("pause");
			return;
		}
	}
	printf("해당하는 책을 찾을 수 없습니다.\n");
	printf("======================================\n");
	system("pause");
}

void Delete(book* books) {
	int i = 0;
	int bookNumber = 0;
	printf("======================================\n");
	printf("삭제할 책 번호를 입력해 주세요: ");
	scanf("%d", &bookNumber);
	fflush(stdin);
	for(i = 0; i < bookCount - 1; i++) {
		if(bookNumber == books[i].bookNumber) {
			break;
		}
	}
	for( ; i < bookCount - 1; i++) {
		books[i] = books[i+1];
	}
	bookCount--;
	printf("======================================\n");
	printf("삭제되었습니다.\n");
	printf("======================================\n");
	system("pause");
}

void Exit(void) {
	free(allBooks);
	exit(0);
}
