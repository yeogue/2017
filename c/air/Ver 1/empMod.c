#include "air.h"

void empMod(LIST* empList) {
	EMP* emp;
	NODE* empNode;
	char name[NAMELEN];
	int select = 0;

	empListPrint(empList);

	empNode = empList->head;

	if(empNode == NULL) {
		printf("등록된 직원이 없음\n");
		system("pause");
		return;
	}

	printf("수정할 직원 이름 입력: ");
	fflush(stdin);
	gets(name);

	while(empNode != NULL) {
		if(!strcmp(name, ((EMP*)empNode->data)->name)) {
			emp = (EMP*)empNode->data;
			break;
		}
		empNode = empNode->next;
	}

	if(empNode == NULL) {
		printf("해당하는 직원이 없음\n");
		system("pause");
		return;
	}

	while(1) {
		printf("[1] 이름 수정\n");
		printf("[2] 나이 수정\n");
		printf("번호 입력: ");
		fflush(stdin);
		scanf("%d", &select);
		if(select < 0 && select > 3) {
			printf("잘못 입력함\n");
		}
		else {
			break;
		}
	}
		
	if(select-1) { // 나이 수정
		if(!strcmp(name, emp->name)) {
			printf("수정할 나이 입력: ");
			fflush(stdin);
			scanf("%d", &emp->age);
		}
	}
	else { // 이름 수정
		if(!strcmp(name, emp->name)) {
			printf("수정할 이름 입력: ");
			fflush(stdin);
			gets(emp->name);
		}
	}
	printf("수정 완료\n");
	system("pause");
}
