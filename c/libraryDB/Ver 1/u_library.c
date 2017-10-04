#include "library.h"

int loginNum = 0;
NODE* loginNode;

void signUp(LIST* userList) {
	 USER* newUser;
	 NODE* userNode;
	 NODE* HEAD = userList->head;
	 NODE* TAIL = userList->tail;

	 newUser = (USER*)malloc(sizeof(USER));
	 userNode = (NODE*)malloc(sizeof(NODE));
	 userNode->data = newUser;

	 if(HEAD == NULL) {
		 userList->head = userNode;
		 userList->tail = userNode;
	 }
	 else {
		 TAIL->next = userNode;
		 userNode->prev = TAIL;
		 userList->tail = userNode;
	 }
	 inputUserInfo(newUser);
}

void inputUserInfo(USER* newUser) {
	printf("아이디 입력: ");
	fflush(stdin);
	gets(newUser->id);
	printf("비밀번호 입력: ");
	fflush(stdin);
	gets(newUser->password);

	printf("이름 입력: ");
	fflush(stdin);
	gets(newUser->userName);
	newUser->bookName = NULL;
	printf("유저 생성 완료\n");
	system("pause");
}

///////////////////////////////////////////

void login(LIST* userList) {
	NODE* userNode;
	int num = 0;
	char id[IDLEN] = {NULL};
	char password[PASSWORDLEN] = {NULL};

	printf("==로그인==\n");
	printf("아이디: ");
	fflush(stdin);
	gets(id);
	printf("비밀번호: ");
	fflush(stdin);
	gets(password);
	userNode = userList->head;
	while(strcmp(id, ((USER*)userNode->data)->id)) {
		userNode = userNode->next;
		if(userNode == NULL) {
			return;
		}
	}
	if(!strcmp(password, ((USER*)userNode->data)->password)) {
		loginNum = 1;
		printf("로그인 성공\n");
		loginNode = userNode;
		system("pause");
	}
	else {
		printf("로그인 실패\n");
		system("pause");
	}
}

///////////////////////////////////////////

void modUser(LIST* userList) {
	NODE* userNode;
	int num = 0;

	if(loginNum != 1) {
		printf("로그인 필요\n");
	}
	else {
		printf("[1] 비밀번호 수정\n");
		printf("[2] 유저명 수정\n");
		printf("번호 입력: ");
		scanf("%d", &num);

		if(num - 2) {
			return modPass(userList, loginNode);
		}
		else {
			return modUserName(userList, loginNode);
		}
	}
}

void modPass(LIST* userList, NODE* loginNode) {
	char password[PASSWORDLEN] = {NULL};

	printf("아이디: %s\n", ((USER*)loginNode->data)->id);
	printf("비밀번호: %s\n", ((USER*)loginNode->data)->password);
	printf("유저명: %s\n", ((USER*)loginNode->data)->userName);
	printf("최근빌린책: %s\n", ((USER*)loginNode->data)->bookName);

	printf("수정할 비밀번호 입력: ");
	fflush(stdin);
	gets(password);
	strcpy(((USER*)loginNode->data)->password, password);
	printf("수정 완료\n");
	system("pause");
}

void modUserName(LIST* userList, NODE* loginNode) {
	char userName[USERNAMELEN] = {NULL};

	printf("아이디: %s\n", ((USER*)loginNode->data)->id);
	printf("비밀번호: %s\n", ((USER*)loginNode->data)->password);
	printf("유저명: %s\n", ((USER*)loginNode->data)->userName);
	printf("최근빌린책: %s\n", ((USER*)loginNode->data)->bookName);

	printf("수정할 유저명 입력: ");
	fflush(stdin);
	gets(userName);
	strcpy(((USER*)loginNode->data)->userName, userName);
	printf("수정 완료\n");
	system("pause");
}

///////////////////////////////////////////

void delUser(LIST* userList) {
	if(loginNum != 1) {
		printf("로그인 필요\n");
	}
	else {
		if(userList->head == userList->tail) {
		}
		else if(userList->head == loginNode) {
			userList->head = loginNode->next;
			userList->head->prev = NULL;
		}
		else if(userList->tail == loginNode) {
			userList->tail = loginNode->prev;
			userList->tail->next = NULL;
		}
		else {
			loginNode->prev->next = loginNode->next;
			loginNode->next->prev = loginNode->prev;
		}
		free((USER*)loginNode->data);
		free(loginNode);
		printf("삭제 완료\n");
		system("pause");
	}
}

///////////////////////////////////////////

void lentBook(LIST* bookList) {
	NODE* bookNode;
	int num = 0;
	
	if(loginNum != 1) {
		printf("로그인 필요\n");
	}
	else {
		printBook(bookList);
		printf("빌릴 책 번호 입력: ");
		scanf("%d", &num);

		bookNode = bookList->head;
		while(bookNode != bookList->tail) {
			if(num == ((BOOK*)bookNode->data)->bookNumber) {
				printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
				printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
				printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
				printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
				if(((BOOK*)bookNode->data)->sign == 'O') {
					((BOOK*)bookNode->data)->sign = 'X';
					((BOOK*)bookNode->data)->userName = ((USER*)loginNode->data)->userName;
					((USER*)loginNode->data)->bookName = ((BOOK*)bookNode->data)->bookName;
					printf("대출 성공\n");
					system("pause");
					return;
				}
			}
			bookNode = bookNode->next;
		}
		if(bookNode == bookList->tail) {
			if(num == ((BOOK*)bookNode->data)->bookNumber) {
				printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
				printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
				printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
				printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
				if(((BOOK*)bookNode->data)->sign == 'O') {
					((BOOK*)bookNode->data)->sign = 'X';
					((BOOK*)bookNode->data)->userName = ((USER*)loginNode->data)->userName;
					((USER*)loginNode->data)->bookName = ((BOOK*)bookNode->data)->bookName;
					printf("대출 성공\n");
					system("pause");
					return;
				}
			}
		}
		printf("대출중이거나 해당하는 책이 없음\n");
		system("pause");
	}
}

///////////////////////////////////////////

void lentList(LIST* bookList) {
	NODE* bookNode;
	char userName[USERNAMELEN];

	printf("%s\n", ((USER*)loginNode->data)->userName);

	if(loginNum != 1) {
		printf("로그인 필요\n");
	}
	else {
		bookNode = bookList->head;
		while(bookNode != bookList->tail) {
			if(&((USER*)loginNode->data)->userName == ((BOOK*)bookNode->data)->userName) {
				printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
				printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
				printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
				printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			}
			bookNode = bookNode->next;
		}
		if(bookNode == bookList->tail) {
			if(&((USER*)loginNode->data)->userName == ((BOOK*)bookNode->data)->userName) {
				printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
				printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
				printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
				printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			}
		}
	}
	system("pause");
}

///////////////////////////////////////////

void returnBook(LIST* bookList) {
	NODE* bookNode;
	char userName[USERNAMELEN];

	printf("%s\n", ((USER*)loginNode->data)->userName);

	if(loginNum != 1) {
		printf("로그인 필요\n");
	}
	else {
		bookNode = bookList->head;
		while(bookNode != bookList->tail) {
			if(&((USER*)loginNode->data)->userName == ((BOOK*)bookNode->data)->userName) {
				printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
				printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
				printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
				printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			}
			if(((BOOK*)bookNode->data)->sign == 'X') {
				((BOOK*)bookNode->data)->sign = 'O';
				((BOOK*)bookNode->data)->userName = NULL;
				((USER*)loginNode->data)->bookName = NULL;
				printf("반납 성공\n");
				system("pause");
				return;
			}
			bookNode = bookNode->next;
		}
		if(bookNode == bookList->tail) {
			if(&((USER*)loginNode->data)->userName == ((BOOK*)bookNode->data)->userName) {
				printf("책번호: %d\n", ((BOOK*)bookNode->data)->bookNumber);
				printf("책이름: %s\n", ((BOOK*)bookNode->data)->bookName);
				printf("보유중: %c\n", ((BOOK*)bookNode->data)->sign);
				printf("대출자: %s\n", ((BOOK*)bookNode->data)->userName);
			}
			if(((BOOK*)bookNode->data)->sign == 'X') {
				((BOOK*)bookNode->data)->sign = 'O';
				((BOOK*)bookNode->data)->userName = NULL;
				((USER*)loginNode->data)->bookName = NULL;
				printf("반납 성공\n");
				system("pause");
				return;
			}
		}
	}
}
