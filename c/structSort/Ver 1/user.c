#include "sort.h"

NODE* falseNode;
void user(LIST* userList) {
	int num = 0;

	while(1) {
		printf("네이버\n");
		printf("[1] 회원 가입\n");
		printf("[2] 정보 출력\n");
		printf("[3] 정보 수정\n");
		printf("[4] 정보 검색\n");
		printf("[5] 정보 삭제\n");
		printf("[6] 종료\n");

		printf("번호 입력: ");
		fflush(stdin);
		scanf("%d", &num);
		system("cls");

		switch(num) {
		case 1:
			userAdd(userList);
			break;
		case 2:
			userPrint(userList);
			break;
		case 3:
			userModify(userList);
			break;
		case 4:
			userSearch(userList);
			break;
		case 5:
			userDelete(userList);
			break;
		case 6:
			return;
			break;
		}
	}
}

void userAdd(LIST* userList) {
	NODE* userNode = newUserAdd(userList);
	if(userNode == falseNode) {
		return;
	}

	if(userList->head == NULL) {
		userList->head = userNode;
		userList->tail = userNode;
	}
	else {
		userList->tail->next = userNode;
		userNode->prev = userList->tail;
		userList->tail = userNode;
		userNode->next = NULL;
	}
}

NODE* newUserAdd(LIST* userList) {
	USER* newUser;
	NODE* idCheck;
	NODE* userNode;

	newUser = (USER*)malloc(sizeof(USER));
	userNode = (NODE*)malloc(sizeof(NODE));

	userNode->data = newUser;
	idCheck = userList->head;

	printf("아이디 입력: ");
	fflush(stdin);
	gets(newUser->id);
	if(userList->head != NULL) {
		if(userList->head != userList->tail) {
			while(idCheck != NULL) {
				if(!strcmp(newUser->id, idCheck->data->id)) {
					printf("아이디가 존재함\n");
					printf("아이디 입력: ");
					fflush(stdin);
					gets(newUser->id);
					idCheck = userList->head;
					continue;
				}
				idCheck = idCheck->next;
			}
		}
		else {
			while(!strcmp(newUser->id, idCheck->data->id)) {
				printf("아이디가 존재함\n");
				printf("아이디 입력: ");
				fflush(stdin);
				gets(newUser->id);
			}
		}
	}
	
	printf("비밀번호 입력: ");
	fflush(stdin);
	gets(newUser->password);
	printf("닉네임 입력: ");
	fflush(stdin);
	gets(newUser->userName);
	printf("회원가입 완료\n");
	system("pause");
	system("cls");

	return userNode;
}

///////////////////////////////////////////////

void userDelete(LIST* userList) {
	NODE* userNode;
	
	userNode = userSearch(userList);

	if(userList->head == userList->tail) {
		userList->head = NULL;
		userList->tail = NULL;
		free(userNode->data);
		free(userNode);
	}
	else if(userNode == userList->head) {
		userList->head = userNode->next;
		userNode->next->prev = NULL;
		free(userNode->data);
		free(userNode);
	}
	else if(userNode == userList->tail) {
		userList->tail = userNode->prev;
		userNode->prev->next = NULL;
		free(userNode->data);
		free(userNode);
	}
	else {
		userNode->prev->next = userNode->next;
		userNode->next->prev = userNode->prev;
		free(userNode->data);
		free(userNode);
	}
	printf("삭제 완료\n");
	system("pause");
	system("cls");
}

///////////////////////////////////////////////

void userPrint(LIST* userList) {
	NODE* userNode;

	userNode = userList->head;

	if(userList->head == NULL) {
		printf("등록된 계정이 없음.\n");
		system("pause");
		system("cls");
		return;
	}
	else if(userList->head == userList->tail) {
		printf("아이디: %s\n", userNode->data->id);
		printf("패스워드: %s\n", userNode->data->password);
		printf("닉네임: %s\n", userNode->data->userName);
		system("pause");
		system("cls");
		return;
	}
	
	while(userNode != NULL) {
		printf("아이디: %s\n", userNode->data->id);
		printf("패스워드: %s\n", userNode->data->password);
		printf("닉네임: %s\n", userNode->data->userName);
		userNode = userNode->next;
	}
	system("pause");
	system("cls");
}

///////////////////////////////////////////////

void userModify(LIST* userList) {
	NODE* userNode;
	int num = 0;
	
	userNode = userSearch(userList);
	if(userNode == 0) {
		return;
	}

	printf("[1] 비밀번호 수정\n");
	printf("[2] 닉네임 수정\n");

	printf("번호 선택: ");
	scanf("%d", &num);

	switch(num) {
	case 1:
		userPasswordMod(userNode);
		break;
	case 2:
		userNameMod(userNode);
		break;
	}
}

void userNameMod(NODE* userNode) {
	char userName[USERNAMELEN];

	printf("수정할 이름 입력: ");
	fflush(stdin);
	gets(userName);

	strcpy(userNode->data->userName, userName);

	printf("아이디: %s\n", userNode->data->id);
	printf("패스워드: %s\n", userNode->data->password);
	printf("닉네임: %s\n", userNode->data->userName);
	printf("수정 완료\n");
	system("pause");
	system("cls");
}

void userPasswordMod(NODE* userNode) {
	char password[PASSWORDLEN];

	printf("수정할 패스워드 입력: ");
	fflush(stdin);
	gets(password);

	strcpy(userNode->data->password, password);

	printf("아이디: %s\n", userNode->data->id);
	printf("패스워드: %s\n", userNode->data->password);
	printf("닉네임: %s\n", userNode->data->userName);
	printf("수정 완료\n");
	system("pause");
	system("cls");
}

///////////////////////////////////////////////

NODE* userSearch(LIST* userList) {
	char userID[IDLEN];
	NODE* userNode;

	if(userList->head == NULL) {
		printf("데이터가 없음.\n");
		system("pause");
		system("cls");
		return 0;
	}

	printf("유저 아이디 입력: ");
	fflush(stdin);
	gets(userID);

	userNode = userList->head;

	if(userList->head == userList->tail) {
		if(!strcmp(userNode->data->id, userID)) {
			printf("아이디: %s\n", userNode->data->id);
			printf("패스워드: %s\n", userNode->data->password);
			printf("닉네임: %s\n", userNode->data->userName);
			system("pause");
			system("cls");
			return userNode;
		}
		else {
			return 0;
		}
	}
	while(userNode != NULL) {
		if(!strcmp(userNode->data->id, userID)) {
			printf("아이디: %s\n", userNode->data->id);
			printf("패스워드: %s\n", userNode->data->password);
			printf("닉네임: %s\n", userNode->data->userName);
			system("pause");
			system("cls");
			return userNode;
		}
		userNode = userNode->next;
	}
	printf("등록된 아이디가 없음.\n");
	system("pause");
	system("cls");	
	return 0;
}

///////////////////////////////////////////////

USER* pointerArray(LIST* userList, int* arraySize) {
	NODE* userNode;
	USER* userArray;
	int num = 0;
	int i = 0;

	userNode = userList->head;
	if(userList->head == userList->tail) {
		num++;
	}
	else {
		while(userNode != NULL) {
			num++;
			userNode = userNode->next;
		}
	}

	userArray = (USER*)malloc(sizeof(USER)*num);

	userNode = userList->head;
	if(userList->head == userList->tail) {
		userArray[0] = *(userNode->data);
	}
	else {
		while(userNode != NULL) {
			userArray[i] = *(userNode->data);
			i++;
			userNode = userNode->next;
		}
	}
	*arraySize = num;

	return userArray;
}

///////////////////////////////////////////////

void selectSort(USER* userArray, int arraySize) {
	USER saveUser;
	int i = 0;
	int j = 0;

	printf("입력된 유저 정보 출력\n");
	for(i = 0; i < arraySize; i++) {
		printf("아이디: %s\n", userArray[i].id);
		printf("패스워드: %s\n",userArray[i].password);
		printf("닉네임: %s\n", userArray[i].userName);
	}

	for(i = 0; i < arraySize; i++) {
		for(j = 1; j < arraySize - i; j++) {
			if(strcmp(userArray[j-1].id, userArray[j].id) > 0) {
				saveUser = userArray[j-1];
				userArray[j-1] = userArray[j];
				userArray[j] = saveUser;
			}
		}
	}

	printf("정렬된 유저 정보 출력\n");
	for(i = 0; i < arraySize; i++) {
		printf("아이디: %s\n", userArray[i].id);
		printf("패스워드: %s\n",userArray[i].password);
		printf("닉네임: %s\n", userArray[i].userName);
	}
}
