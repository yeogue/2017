#include "library.h"

void library(void) {
	LIST bookList;
	LIST userList;
	int num = 0;
	int idx = 0;

	bookList.head = NULL;
	bookList.tail = NULL;
	userList.head = NULL;
	userList.tail = NULL;

	printf("[1] 관리자\n");
	printf("[2] 사용자\n");
	printf("[3] 종료\n");
	printf("번호 입력: ");
	scanf("%d", &num);

	while(1) {
		switch(num) {
		case 1: // 관리자
			printf("[1] 도서등록\n");
			printf("[2] 도서목록\n");
			printf("[3] 도서검색\n");
			printf("[4] 도서수정\n");
			printf("[5] 도서삭제\n");
			printf("[6] 돌아가기\n");	
			printf("번호 입력: ");
			scanf("%d", &idx);
			switch(idx) {
			case 1: addBook(&bookList); system("cls"); break;
			case 2: printBook(&bookList); system("cls"); break;
			case 3: searchBook(&bookList); system("cls"); break;
			case 4: modBook(&bookList); system("cls"); break;
			case 5: delBook(&bookList); system("cls"); break;
			case 6: 
				printf("[1] 관리자\n");
				printf("[2] 사용자\n");
				printf("[3] 종료\n");
				printf("번호 입력: ");
				scanf("%d", &num);
				break;
			}
			break;
		case 2: // 사용자
			printf("[1] 회원가입\n");
			printf("[2] 로그인\n");
			printf("[3] 정보수정\n");
			printf("[4] 회원탈퇴\n");
			printf("[5] 도서대여\n");
			printf("[6] 대여목록\n");
			printf("[7] 도서반납\n");
			printf("[8] 돌아가기\n");	
			printf("번호 입력: ");
			scanf("%d", &idx);
			switch(idx) {
			case 1: signUp(&userList); system("cls"); break;
			case 2: login(&userList); system("cls"); break;
			case 3: modUser(&userList); system("cls"); break;
			case 4: delUser(&userList); system("cls"); break;
			case 5: lentBook(&bookList); system("cls"); break;
			case 6: lentList(&bookList); system("cls"); break;
			case 7: returnBook(&bookList); system("cls"); break;
			case 8: 
				printf("[1] 관리자\n");
				printf("[2] 사용자\n");
				printf("[3] 종료\n");
				printf("번호 입력: ");
				scanf("%d", &num);
				break;
			}
			break;
		case 3: // 종료

			return;
		}
	}
}
